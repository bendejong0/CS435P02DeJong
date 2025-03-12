#include <stdio.h>
#include <stdlib.h>
#include "scanner.c"
enum tokenType currentToken;

// run the scanner on the thing
// get an initial token
// use if else logic to match expected tokens with stuff
// if its not an expected token then blow up
// otherwise yoink another token

void expression();
void term();
void factor();
void read();
void write();
void match(enum tokenType expected);
unsigned numErrs;

void statement() {
	if (currentToken == ID) {
		// it HAS to be Identifier followed by ASSIGN;
		currentToken = scan();
		match(ASSIGN);
		expression();
	}
	else if (currentToken == READ) {
		read();
	}
	else if (currentToken == WRITE) {
		write();
	}
	else {
		//parse_error("Invalid statement", mnemonic[currentToken]);
	}
	match(SEMICOLON);
}

void expression() {
	//expressions are made of sums of terms
	term();
	while (currentToken == PLUS || currentToken == MINUS) {
		currentToken = scan();
		term();
	}
}

void term() {
	// terms are made of prodcts of factors
	factor();
	// check for times or divide by scanning
	while (currentToken == TIMES || currentToken == DIV) {
		currentToken = scan();
		factor();
	}

}

void factor() {
	// yoink a first token
	// current token is assign, but YUCK!
	// so bring in the next one to compare it to the guys.
	if (currentToken == ID || currentToken == NUMBER) {
		currentToken = scan();
	}
	else if (currentToken == LPAREN) {
		currentToken = scan();
		expression();
		match(RPAREN);
	}
}

void read() {
	currentToken = scan();
	match(LPAREN);
	match(ID);
	while (currentToken == COMMA) {
		currentToken = scan();
		match(ID);
	}
	match(RPAREN);
}

void write() {
	currentToken = scan();
	match(LPAREN);
	expression();
	match(RPAREN);
}



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
		printf("Actual: %s ", mnemonic[currentToken]);
		exit(1);
	}
}




void main(int argc, char* argv[]) {

	extern FILE* src;

	if (argc > 1) {
		if (fopen_s(&src, argv[1], "r")) {
			fprintf(stderr, "Error opening source file: %s ", argv[1]);
			exit(1);
		}
	}
	currentToken = scan();
	while (currentToken != SCAN_EOF) {
		statement();
	}
	printf("YIPPE!");

	fclose(src);

}