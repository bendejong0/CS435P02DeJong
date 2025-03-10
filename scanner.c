//starter code for Simple_PL1 scanner
#include <stdio.h> //for c I/o
#include <stdlib.h> // for exit()
#include <ctype.h> // for isalpha(), isalnum(), ...
enum tokenType {
	READ, WRITE, ID, NUMBER, LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGN, PLUS, MINUS, TIMES, DIV, SCAN_EOF
};
char* mnemonic[] = { "READ", "WRITE", "ID", "NUMBER", "LPAREN", "RPAREN", "SEMICOLON", "COMMA",
"ASSIGN", "PLUS", "MINUS", "TIMES", "DIV", "SCAN_EOF" };
void lexical_error(char ch)
{
	fprintf(stderr, "Lexical Error. Unexpected character: %c.\n", ch);
}
char lexeme[256] = { '\0' };
unsigned int lexLen = 0;
FILE* src;
enum tokenType scan()
{
	static int currentCh = ' ';
	static int tempCh = ' ';
	char* reserved[2] = { "read", "write" };
	lexLen = 0; // clear lexeme buffer for each scan
	lexeme[0] = '\0';
	extern FILE* src; //pointer to FILE handle that binds to source file.
	if (feof(src)) {
		return SCAN_EOF;
	}
	while ((currentCh = fgetc(src)) != EOF) {
		if (currentCh == ";") {
			return SEMICOLON;
		}
		else if (currentCh == '+') {
			return PLUS;
		}
		else if (currentCh == '-') {
			return MINUS;
		}
		else if (currentCh == '/') {
			return DIV;
		}
		else if (currentCh == '*') {
			return TIMES;
		}
		else if (currentCh == ':') {
			tempCh = fgetc(src);
			if (tempCh == '=') {
				return ASSIGN;
			}
			else {
				ungetc(tempCh, src);
				lexical_error(currentCh);
				continue;
			}
		}
		else if (currentCh == ',') {
			return COMMA;
		}
		else if (currentCh == '(') {
			return LPAREN;
		}
		else if (currentCh == ')') {
			return RPAREN;
		}
		else if (currentCh == ';') {
			return SEMICOLON;
		}
		// if it's a space, skip
		else if (isspace(currentCh)) {
			continue;
		}
		// if it's a letter or underscore,
		else if (isalpha(currentCh) || currentCh == '_') { //needs to be modified

			lexeme[0] = currentCh;
			lexLen = 1;
			// checks to see lexemes are legal, getting 1 character at a time
			for (tempCh = fgetc(src); isalnum(tempCh) || tempCh == '_'; tempCh = fgetc(src)) {
				lexeme[lexLen] = tempCh;
				lexLen++;
			}
			lexeme[lexLen] = '\0';
			ungetc(tempCh, src); //put back character that is not a alpha/digit or �_�
			// see if lexeme is a reserved word, if not, return ID.
			if (strcmp(lexeme, reserved[0]) == 0) {
				return READ;
			}
			else if (strcmp(lexeme, reserved[1]) == 0) {
				return WRITE;
			}
			lexLen = 0;
			return ID;
		}
		else if (isdigit(currentCh)) {
			lexeme[0] = currentCh;
			lexLen = 1;
			// build lexeme for number
			// finish fixing lexeme string, ungetc the last character read that is not a digit and then return NUMBER
			for (tempCh = fgetc(src); isdigit(tempCh); tempCh = fgetc(src)) {
				lexeme[lexLen] = tempCh;
				lexLen += 1;
			}
			lexeme[lexLen] = '\0';
			ungetc(tempCh, src); //put back character that is not a digit
			return NUMBER;

		}

		// use selection statements to look for tokens for operators and delimiters and assignment (:=)
		else {
			lexical_error(currentCh);
		}
	}
	return SCAN_EOF;
}
