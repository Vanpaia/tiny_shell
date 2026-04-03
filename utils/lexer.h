#ifndef LEXER_H
#define LEXER_H

#include "../config.h"
#include "../models.h"

/* This struct contains all the elements of a single token */
struct ShellToken {
	char string[BUFFER_SIZE];
	char type[4];
};

/* This function will tokenize the user input to break it down into smaller parts to parse */
int tokenize(char* c);

/* This function will parse the tokens for commands, flags, and others */
int parse(char* c, int* cmt);

#endif
