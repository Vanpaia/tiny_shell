#include "lexer.h"
#include "../config.h"

#include <stdio.h>

/* This first lexer version assumes ASCII input only (pointer arithmatic) and should be upgraded to UTF-8 in due time */
/* It also only reads tokens that have been pre-processed by strtok, as such it also returns whether a comment is still open */
int tokenize(char* c, int* cmt) {
	char str_buffer[(BUFFER_SIZE / 2)];
	char token_type[4];

	while (*c != '\0') {
		/* Check for the type of token based on the signals (- for flags, " for comments, in combination with whether we are already in a comment (cmt) ) */
		if (*cmt == 0) {
			if (token_type[0] == '\0' && strcmp(c, "-") == 0) {
				strncpy(token_type, "flg", 3);
				token_type[3] = '\0';
				c++;
				continue;
			} else if (token_type[0] == '\0' && strcmp(c, "\"") == 0) {
				strncpy(token_type, "cmt", 3);
				token_type[3] = '\0';
				*cmt = 1;
				c++;
				continue;
			} else if (token_type[0] == '\0') {
				strncpy(token_type, "cmd", 3);
				token_type[3] = '\0';
				c++;
				continue;
			}
		} else if (*cmt == 1) {
			strncpy(token_type, "cmt", 3);
			token_type[3] = '\0';
			if (strcmp(c, "\"") == 0) {
				*cmt = 0;
				c++;
				continue;
			} 
		}
		if (strcmp(c, "\"") != 0) {
			str_buffer[strlen(str_buffer)] = *c;
			str_buffer[strlen(str_buffer)+1] = '\0';
			printf("%c", *c);
		}
		c++;
	}
	return 0;
}
