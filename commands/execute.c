#include "execute.h"
#include "help_text.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int execute_command(struct ShellCommand *c) {

	/* Parse successful, matching commands */
	if (strcmp(c->cmd, "exit") == 0) {
		exit(EXIT_SHELL);
	} else if (strcmp(c->cmd, "echo") == 0) {
		printf("%s\n", c->extra_input);
		exit(EXIT_SUCCESS);
	} else if (strcmp(c->cmd, "help") == 0) {
		printf("%s\n", help_text);
		exit(EXIT_SUCCESS);
	} else {
		char *argv[c->flag_no+1];
		argv[0] = c->cmd;
		
		int i;
		for (i = 1; i <= (c->flag_no); i++) {
			argv[i] = c->flags[i-1];
		}
		argv[c->flag_no+1] = NULL;
		execvp(c->cmd, argv);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
