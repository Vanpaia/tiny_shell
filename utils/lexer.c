#include "lexer.h"
#include "../config.h"

#include <stdio.h>
#include <string.h>


/* This function resets the shell command struct to be used for the next input */
int reset_token(struct ShellToken *c) {
	memset(c, 0, sizeof(struct ShellToken));
	return 0;
}

/* This first lexer version assumes ASCII input only (pointer arithmatic) and should be upgraded to UTF-8 in due time */
/* It also only reads tokens that have been pre-processed by strtok, as such it also returns whether a comment is still open */
int tokenize(char* c) {
	char str_buffer[(BUFFER_SIZE / 2)];

	struct ShellToken token = {0};

	while (*c != '\0') {
		/* Check for the type of token based on the signals (- for flags, " for quote, in combination with whether we are already in a comment (cmt) ) */
		if (strcmp(c, " ") == 0 || strcmp(c, ";") == 0) {
			if (token.string[0] != '\0') {
				printf("%s - %s\n", token.type, token.string);
				reset_token(&token);
			}
			c++;
		}
		if (token.type[0] == '\0') {
			if (strcmp(c, "-") == 0) {
				strncpy(token.type, "flg", 3);
				c++;
				continue;
			} else if (strcmp(c, "\"") == 0) {
				strncpy(token.type, "qte", 3);
				c++;
				continue;
			} else {
				strncpy(token.type, "cmd", 3);
				c++;
				continue;
			}
		}

			strncpy(token.type, "cmt", 3);
			token.type[3] = '\0';
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


/* This first lexer version assumes ASCII input only (pointer arithmatic) and should be upgraded to UTF-8 in due time */
/* It also only reads tokens that have been pre-processed by strtok, as such it also returns whether a comment is still open */
int parse(char* c, int* cmt) {
	char str_buffer[(BUFFER_SIZE / 2)];
	char token.type[4];

	while (*c != '\0') {
		/* Check for the type of token based on the signals (- for flags, " for comments, in combination with whether we are already in a comment (cmt) ) */
		if (*cmt == 0) {
			if (token.type[0] == '\0' && strcmp(c, "-") == 0) {
				strncpy(token.type, "flg", 3);
				token.type[3] = '\0';
				c++;
				continue;
			} else if (token.type[0] == '\0' && strcmp(c, "\"") == 0) {
				strncpy(token.type, "cmt", 3);
				token.type[3] = '\0';
				*cmt = 1;
				c++;
				continue;
			} else if (token.type[0] == '\0') {
				strncpy(token.type, "cmd", 3);
				token.type[3] = '\0';
				c++;
				continue;
			}
		} else if (*cmt == 1) {
			strncpy(token.type, "cmt", 3);
			token.type[3] = '\0';
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
