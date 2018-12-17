#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include "board.h"

typedef char *Symbol[8];

extern Symbol A, B, C, D, E, F, G, H, I, J, K, L, M, O, P, Q, R, S, T, U, V, W;
extern Symbol X, Y, Z;
extern Symbol zero, one, two, three, four, five, six, seven, eight, nine;
extern Symbol none, minus, plus, mul, divide, equal, tilde, hyphen;
extern Symbol excl_mark, question_mark, ampersand, at, smiley;

/* convert_init
 *   initialize symbol generation
 */
void convert_init();

/* convert_symbol
 *   generate an 8 byte data stream to buf[] according to symbol s
 */
void convert_symbol( uint8 *buf, Symbol s);

/* convert_stream
 *   generate data stream to buf[] according to the array s[] of symbol pointers
 *   if sym_width==0, each symbol must have a white column which acts as a separator, so
 *   that symbols can have different widthes,
 *   else sym_width indicates the symbols in the input stream have FIXED WIDTH 'sym_width'.
 *   It returns the number of bytes generated
 */
uint32 convert_stream(uint8 *buf, Symbol *s[], int32 sym_width);

/* convert_text
 *   generates a byte stream to buf[] representing the chars in string s, returns the
 *   number of bytes in the stream.
 *   supported chars : A-Z, 1-2, +, -, *, /, ., !, ?, ~, &, @, whitespace
 */
uint32 convert_text(uint8 *buf, char* s);

/* convert_ftext
 *   generates a byte stream to buf[] according to formatted string (%d, %x, %s, %c)
 */
uint32 convert_ftext(uint8* buf, const char* fmt, ...);

#endif
