#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../config.h"
#include "../models.h"
#include "../commands/execute.h"

int test_builtins() {
	struct ShellCommand test_cmd;
	/* First we set up a standard echo command with 'Test' output */
	reset_command(&test_cmd);
	strncpy(test_cmd.cmd, "echo", 15);
	strncpy(test_cmd.extra_input, "Test", (BUFFER_SIZE/2));


	int pipefds[2];
	char buffer[100] = {0};

	/* Create a pipe and save stdout to pipe */
	pipe(pipefds);
	int old_stdout = dup(STDOUT_FILENO);
	dup2(pipefds[1], STDOUT_FILENO);

	/* Create 'Test' as stdout flush it */
	int result = execute_command(&test_cmd);
	fflush(stdout);

	/* Close pipe and restore stdout */
	close(pipefds[1]);
	dup2(old_stdout, STDOUT_FILENO);

	/* Pipe to buffer and assert 'Test' */
	read(pipefds[0], buffer, 100);
	assert(result == 0 && "Expected echo command to execute succesfully");
	assert(strcmp(buffer, "Test") == 0 && "Expected 'Test' to be printed to stdout with echo");
	return 0;
	}

int main() {
    test_builtins();
    printf("All tests passed!\n");
    return 0;
}
