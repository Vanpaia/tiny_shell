#include "models.h"
#include <string.h>

/* This function resets the shell command struct to be used for the next input */
int reset_command(struct ShellCommand *c) {
	memset(c, 0, sizeof(struct ShellCommand));
	return 0;
}
