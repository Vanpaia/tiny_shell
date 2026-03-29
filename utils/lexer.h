#ifndef LEXER_H
#define LEXER_H

#include "../config.h"
#include "../models.h"

/* This function will parse the user input for commands, flags, and others */
int tokenize(char* c, int* cmt);

#endif
