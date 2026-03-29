#ifndef MODELS_H
#define MODELS_H

#include "config.h"

/* This struct contains the state of the current shell session */
struct SessionState {
	int state;
};

/* This struct contains all the elements of a single user command */
struct ShellCommand {
	char line[BUFFER_SIZE];
	char cmd[16];
	int cmd_no;
	char flags[MAX_FLAGS][16]; 
	int flag_no;
	int extra_state;
	char extra_input[BUFFER_SIZE/2];
	int extra_len;
};

/* This function will reset the command */
int reset_command(struct ShellCommand *c);

#endif
