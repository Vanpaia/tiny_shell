#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>


#include "config.h"
#include "models.h"
#include "utils/parser.h"
#include "commands/execute.h"


int main() {
	/* Create the ShellCommand structure used to communicate and execute user input and set session state */
	struct ShellCommand user_cmd; 
	struct SessionState session = { .state = 1 }; 
	int* session_id = &session.state;
	
	/* Start main loop */
	while (session.state == 1) {
		reset_command(&user_cmd);

		/* This is the shell prompt and the user input */
		printf("marginella> ");
		if (fgets(user_cmd.line, BUFFER_SIZE, stdin) == NULL) {
			printf("Error reading line, max buffer size is %i\n", BUFFER_SIZE);
			return 1;
		}
		
		/* Parse user input using parser.c */
		int parse_result = parse_user_input(&user_cmd);
		if (parse_result == 0) {
			/* Create a new procedure for each command to be executed */
			int i;
			for (i=0; i < user_cmd.cmd_no; i++) {
				pid_t id = fork();

				if (id == 0) {
					/* The child process executes the command and exits*/
					execute_command(&user_cmd);
				} else {
					/* The parent process checks to see for the exit code that quits the shell*/
					int status;
					waitpid(id, &status, 0);
					int exit_status = WEXITSTATUS(status);        
					if ( exit_status == EXIT_SHELL ) {
						printf("Goodbye, little shell!\n");
						*session_id = 0;
					}
				}
			}
		}

	}

	return 0;
}
