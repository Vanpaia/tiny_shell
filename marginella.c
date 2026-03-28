#include<stdio.h>
#include<string.h>


#include "config.h"
#include "models.h"
#include "parser.h"

int main() {
	struct ShellCommand user_cmd; 
	struct SessionState session = { .state = 1 }; 
	
	/* Start main loop */
	while (session.state == 1) {
		reset_command(&user_cmd);

		printf("marginella> ");
		if (fgets(user_cmd.line, BUFFER_SIZE, stdin) == NULL) {
			printf("Error reading line, max buffer size is %i\n", BUFFER_SIZE);
			return 1;
		}
		
		/* Parse user input using parser.c */
		int parse_result = parse_user_input(&user_cmd);
		if (parse_result == 0) {
			printf("%s\n", user_cmd.cmd);
			printf("%s\n", user_cmd.extra_input);
			/* Parse successful, matching commands */
			if (strcmp(user_cmd.cmd, "exit") == 0) {
				session.state = 0;
			}
		}

	}

	return 0;
}
