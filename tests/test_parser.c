#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../config.h"
#include "../models.h"
#include "../utils/parser.h"

int test_parse_buffer() {
	struct ShellCommand test_cmd;
	/* First we test a command that is too long */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "CommandCommandCommand -f \"Whatever\"", BUFFER_SIZE);
	int result = parse_user_input(&test_cmd);
	assert(result == 2 && "Expected error due to command being too long");
	/* Second we test a flag that is too long */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "Command -FlagsFlagsFlagsFlags -Flags -Flags -Flags \"Whatever\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 1 && "Expected error due to flag being too long");
	/* Third we test an extra_input that is too long */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "Command -f \"CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 3 && "Expected error due to extra_input being too long");
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "Command -f \"Comment CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 3 && "Expected error due to extra_input being too long");
	return 0;
}

int test_parse_cmd() {
	struct ShellCommand test_cmd;
	/* First we test a simple valid cmd */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo", BUFFER_SIZE);
	int result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0 && "Expected command to be 'echo'");
	/* Second we test two valid cmd, second is ignored */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo hello", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0 && "Expected command to be 'echo' and hello to be ignored");
	/* Third we test an invalid cmd */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "-Echo hello", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 2 && "Expected parse_user_input to fail on flag instead of command");
	/* Fourth we test an invalid cmd */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == -1 && "Expected parse_user_input to fail on empty input");
	return 0;

}

int test_parse_flags() {
	struct ShellCommand test_cmd;
	/* First we test a cmd plus a valid amount of flags */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo -a -b -c -d", BUFFER_SIZE);
	int result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(test_cmd.flag_no == 4);
	/* Second we test a cmd plus an invalid amount of flags */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo -a -b -c -d -e -f", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 1);
	/* Third we test a cmd plus a flag in quotes */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo -a \"-b\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(test_cmd.flag_no == 1);
	return 0;
}

int test_parse_quotes() {
	struct ShellCommand test_cmd;
	/* First we test a cmd plus a valid multi-word string */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo \"Hello World!\"", BUFFER_SIZE);
	int result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(strcmp(test_cmd.extra_input, "Hello World!") == 0 && "Expected multiple word string to be parsed 'Hello World!'");
	/* Second we test a cmd plus a valid one word string */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo \"Hello\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(strcmp(test_cmd.extra_input, "Hello") == 0 && "Expected single word string to be parsed 'Hello'");
	/* Third we test a cmd plus an unclosed string */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo \"Hello World!", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(strcmp(test_cmd.extra_input, "Hello World!") == 0 && "Expected input to be 'Hello World!' regardless of unclosed string");
	/* Fourth we test a cmd plus an empty string */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo \"\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0);
	assert(strcmp(test_cmd.cmd, "echo") == 0);
	assert(strcmp(test_cmd.extra_input, "") == 0 && "Expected input to be an empty string");
	/* Fifth we test a cmd plus two strings */
	reset_command(&test_cmd);
	strncpy(test_cmd.line, "echo \"Hello\" \"World\"", BUFFER_SIZE);
	result = parse_user_input(&test_cmd);
	assert(result == 0 && "Expected parse_user_input to succeed");
	assert(strcmp(test_cmd.cmd, "echo") == 0 && "Expected command to be 'echo'");
	assert(strcmp(test_cmd.extra_input, "Hello") == 0 && "Expected extra_input to be 'Hello' and 'World' to be ignored");
	return 0;
}

int main() {
    test_parse_buffer();
    test_parse_cmd();
    test_parse_flags();
    test_parse_quotes();
    printf("All tests passed!\n");
    return 0;
}
