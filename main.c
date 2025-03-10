#include <stdio.h>
#include <stdlib.h>
#include "scanner.c"
enum tokenType currentToken;
FILE* src;

void parse_error(char* errMsg, char* lexeme) {
	extern unsigned numErrs; //for future if error recovery used
	numErrs++;
	fprintf(stderr, "%s: %s\n", errMsg, lexeme);
}
void match(enum tokenType expected)
{
	if (currentToken == expected) {
		currentToken = scan();
	}
	else {
		parse_error("Expected symbol", mnemonic[expected]);
		exit(1);
	}
}

int parse() {
	scan(); E();
	if (currentToken != EOK_TOK) {
		parse_error("Unexpected end of input", );
	}
}

void main() {

	if (parse() == 0) {

	}

}