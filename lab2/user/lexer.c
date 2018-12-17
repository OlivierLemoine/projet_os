#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "lexer.h"

typedef struct {
	char			name[8];
	TokenType		tok;
} CMD;

CMD cmds[]={
	{"di", T_DISK_INIT},
	{"ds", T_DISK_STATUS},
	{"dd", T_DISK_DUMP},
	{"mount", T_MOUNT},
	{"stat", T_STAT},
	{"ls", T_LS},
	{"cat", T_CAT},
	{"echo", T_ECHO},
	{"help", T_HELP}
};

/* Token data */
TokenType token;				/* current token type*/
int token_val;					/* token value, if current token is T_NUM */
char token_str[MAX_STR_LEN];	/* token value, if current token is T_LABEL */

#define IS_BINARY_DIGIT(ch) ((ch)=='0' || ((ch)=='1'))
#define IS_HEXA_DIGIT(ch) (((ch)>='0' && (ch)<='9') || ((ch)>='a' && (ch)<='f') || ((ch)>='A' && (ch)<='F'))
#define IS_DIGIT(ch) ((ch)>='0' && (ch)<='9')
#define IS_LC_LETTER(ch) ((ch)>='a' && (ch)<='z')
#define IS_UC_LETTER(ch) ((ch)>='A' && (ch)<='Z')
#define IS_LETTER(ch) (((ch)>='a' && (ch)<='z') || ((ch)>='A' && (ch)<='Z'))

/*globals that the scanner uses*/
static unsigned char *line;					/* the current line being scanned */
static unsigned char* next;					/* next character */

/* scanner_reset
 *
 * reset the scanner at the beginning of the file
 */
void lexer_reset(char* s)
{
	line=s;
	next=line;
}

/* skip_space
 *
 * skips over any whitespace coming up next in the string.  if there
 * is a comment, it is treated as the end of the line.
 */
static void skip_space()
{
	while ((*next == ' ') || (*next == '\t')) {
//		*next=' ';
		next++;
	}
} 


/* scan_word : scan for a name. This name may be :
 *   - a label   : the token_str variable is assigned with this name.
 *   - a keyword : the token_val variable is assigned with the keyword index
 *                 in the instruction table.
 */
static void scan_word()
{
	unsigned char ch=*next++;
	int i=0;

	/*words may be letters or digits*/
	while ((IS_LC_LETTER(ch)) || (IS_UC_LETTER(ch)) || (IS_DIGIT(ch)) || ch=='_' || ch=='/' || ch=='.' || ch=='~') {
		token_str[i] = tolower(ch);
		i++;
		ch=*next++;
	}
	next--;
	token_str[i] = '\0';
	token = T_TEXT;

	/* is the text a keyword ? */
	for (i=0 ; i<(sizeof(cmds)/sizeof(CMD)); i++) {
		if (strcmp(token_str,cmds[i].name)==0) {
			token = cmds[i].tok;
//			token_val = i;
			break;
		}
	}
}

/* scan_number : 
 *
 * @name	scan_number
 * @return	the value as int
 *
 * scan a number from the string and return an integer. It can scan
 * - binary numbers  : 0b011011, 0B1101 (only integer values)
 * - hexa numbers    : 0x12fa, 0X1FcD5  (only integer values)
 * - decimal numbers : 12, 674
 */
static int scan_number()
{
	unsigned char ch=*next++;
	int val=0;
	
	token = T_NUM;
	
	if (ch=='0') {
		ch=*next++;
		if (ch=='x' || ch=='X') {		// hexadecimal number
			ch=*next++;
			while (1) {
				if (IS_DIGIT(ch))
					val=16*val+(ch-'0');
				else if (IS_LC_LETTER(ch))
					val=16*val+(ch-'a'+10);
				else if (IS_LC_LETTER(ch))
					val=16*val+(ch-'A'+10);
				else break;
				ch=*next++;
			}
			next--;
			return val;
		}
		if (ch=='b' || ch=='B') {		// binary number
			ch=*next++;
			while (IS_BINARY_DIGIT(ch)) {
				val=2*val+(ch-'0');
				ch=*next++;
			}
			next--;
			return val;
		}
		next--;
		return 0;
	}
	/* scan decimal values */
	while (IS_DIGIT(ch)) {
    	val = 10 * val + (ch - '0');
    	ch=*next++;
	}
	next--;
	return val;
}


/* Get the next token on the current line */
void next_token()
{
	token=T_NONE;
	skip_space();
	if (IS_LETTER(*next) || *next=='_' || *next=='/')		/*words must start with a letter*/
		scan_word();
	else if (IS_DIGIT(*next))
		token_val=scan_number();
	else if (*next=='-') {
		next++;
		if (IS_DIGIT(*next)) {
			token_val=-scan_number();
		}
	} else if (*next==10 || *next==13 || *next==0 || *next==';')
		token=T_EOL;
	else if (*next=='?') token = T_HELP;
	else if (*next=='(') token = T_LPAREN;
	else if (*next==')') token = T_RPAREN;
	else if (*next=='+') token = T_PLUS;
	else if (*next=='-') token = T_MINUS;
	else if (*next=='*') token = T_STAR;
	else if (*next=='/') token = T_SLASH;
	else token = T_ERROR;
} 
/*
void print_error_mark()
{
	unsigned int i;
	
	for (i=0 ; i<(unsigned int)(next-line) ; i++) printf(" ");
	printf("^\n");
}

void print_error(const char *fmt, ...)
{
	va_list args;
	unsigned int i;
	
	term_printf("%s",line);
	for (i=0 ; i<(unsigned int)(next-line) ; i++) term_printf(" ");
	term_printf("^\n");

	va_start(args, fmt);
	vprintf (fmt, args);
	va_end(args);
}
*/
