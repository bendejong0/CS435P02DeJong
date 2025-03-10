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

void F()
{
	if (currentToken == IDENT) scan();
	else if (currentToken == LEFT_P_TOK) {
		scan();
		E();
		if (currentToken == RIGHT_P_TOK)
			scan();
	}
	else syntax_error("Missing Right Parenthesis");
}
else syntax_error("Missing Expression symbol");
}


void E()
{
	T(); while (currentToken == PLUS_TOK) {
		scan();
		T();
	}
}

void T()
{
	F(); while (currentToken == STAR_TOK) {
		scan();
		F();
	}
}

void main() {

	if (parse() == 0) {

	}

}