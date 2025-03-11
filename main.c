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
extern unsigned numErrs;

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
	while(currentToken == TIMES || currentToken == DIV){
		currentToken = scan();
		factor();
	}

}

void read() {
	currentToken = scan();
	match(LPAREN);
	expression();
	currentToken = scan();
	match(RPAREN);
}

void write() {
	currentToken = scan();
	match(LPAREN);
	expression();
	currentToken = scan();
	match(RPAREN);
}

void factor() {
	// yoink a first token
	currentToken = scan();
	if (currentToken == ID || currentToken == NUMBER) {
		return;
	}
	else if (currentToken == LPAREN) {
		expression();
		currentToken = scan();
		match(RPAREN);
	}

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


void statement() {
	if (currentToken == ID) {
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
	else{
		parse_error("Invalid statement", mnemonic[currentToken]);
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

	while ((currentToken = scan()) != SCAN_EOF) {
		statement();
		// make sure the last thing is a semicolon
		currentToken = scan();
		match(SEMICOLON);
	}

	fclose(src);

}