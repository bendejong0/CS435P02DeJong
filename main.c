#include <stdio.h>
#include <stdlib.h>
#include "scanner.c"
tokenType currentToken;

// run the scanner on the thing
// get an initial token
// use if else logic to match expected tokens with stuff
// if its not an expected token then blow up
// otherwise yoink another token

void expression() {
	//expressions are made of sums of terms
	term();
	
}

void term() {
	// terms are made of prodcts of factors
	factor();

}

void factor() {
	// yoink a first token
	currentToken = scan();
	if (currentToken == tokenType::ID) {
		return;
	}
	if (currentToken == tokenType::NUMBER) {
		return;
	}
	if(currentToken == )

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
		exit(1);
	}
}

int parse() {
	
}


void main(int argc, char* argv[]) {

	while (currentToken = scan()) {
		if (currentToken == tokenType::ID) {
			currentToken = scan();
			// 
			match(tokenType::ASSIGN);
			// then call expression
			expression();

		}
		else if (currentToken == tokenType::READ) {

		}
		else if (currentToken == tokenType::WRITE) {

		}
	}

}