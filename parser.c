#include "parser.h"

/* This includes the parser function, turning the user input into a shell command */
/* 0 = Success; -1 = Error: No input; 1 = Error: Too many flags */
int parse_user_input(struct ShellCommand *c) {
	char * pch;
	pch = strtok(c->line, " \n");

	/* Return error no command */
	if (pch == NULL) {
		return -1; 
	}

	while (pch != NULL)
	{
		c->extra_len = strlen(c->extra_input);

		/* Check for command on first place */
		if (c->cmd[0] == '\0') {
			strncpy(c->cmd, pch, 15);
			c->cmd[strlen(pch)] = '\0';
		} else if (pch[0] == '-') {
			if (c->flag_no < 4) {
				strncpy(c->flags[c->flag_no], pch, 15);
				c->flags[c->flag_no][15] = '\0';
			} else {
				printf ("Max flags: %i\n", MAX_FLAGS);

				/* Return error too many flags */
				return 1;
			}
			c->flag_no ++;
		} else if (pch[0] == '"' && c->extra_len <= 1 && c->extra_state == 0) {
			c->extra_state = 1;
			pch ++;
			strncpy(c->extra_input, pch, BUFFER_SIZE/2-2);
			c->extra_input[strlen(c->extra_input)] = ' ';
			c->extra_input[strlen(c->extra_input)+1] = '\0';
			c->extra_input[(BUFFER_SIZE / 2) - 1] = '\0';
		} else if (c->extra_state == 1) {
			strncpy(c->extra_input + c->extra_len, pch, BUFFER_SIZE/2-c->extra_len-1);
			c->extra_input[(BUFFER_SIZE / 2) - 1] = '\0';
			if (pch[strlen(pch)-1] == '"') {
				c->extra_state = 0;
				c->extra_input[strlen(c->extra_input)-1] = '\0';
			} else {
				c->extra_input[strlen(c->extra_input)] = ' ';
				c->extra_input[strlen(c->extra_input)+1] = '\0';
			}
		}
		pch = strtok (NULL, " \n");
	}

	return 0;
}
