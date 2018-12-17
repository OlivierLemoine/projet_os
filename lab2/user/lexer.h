#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <stdio.h>

#define MAX_LINE_LENGTH		80	
#define MAX_STR_LEN			80		/* maximum length of a label */

typedef enum {
	T_DISK_INIT,	/* cmd tokens */
	T_DISK_STATUS,
	T_DISK_DUMP,
	T_MOUNT,
	T_STAT,
	T_LS,
	T_CAT,
	T_ECHO,
	
	T_TEXT,		/* token is a label */
    T_NUM,			/* token is a numerical value */
	
	T_HELP,			/* ? for help token */
	
    T_PLUS,			/* + */
    T_MINUS,		/* - */
    T_STAR,			/* * */
    T_SLASH,		/* / */
    T_LPAREN,		/* ( */
    T_RPAREN,		/* ) */
	
	T_EOL,			/* end of line */
	T_ERROR,
	T_NONE
} TokenType;

/*---------------------------------------------------------------------------
 * Global variables
 *-------------------------------------------------------------------------*/
extern TokenType token;				/* token type */
extern int token_val;				/* token value, if current token is T_NUM */
extern char token_str[MAX_STR_LEN]; /* token value, if current token is T_LABEL*/

/*---------------------------------------------------------------------------
 * Function prototypes
 *-------------------------------------------------------------------------*/

/* scanner_reset
 *
 * resets the scanner at the beginning of the current scanned file. If
 * infile is not the current scanned file, the scanner is initialized with
 * infile after closing the current file.
 */
void lexer_reset(char* s);

/* scanner_next_token
 *
 * gets the next token in the current string. The value of the current token
 * is stored in the 'token' global variable, and
  also sets the token_val and token_str variables as appropriate. */
void next_token();

#endif /* _SCANNER_H_ */
