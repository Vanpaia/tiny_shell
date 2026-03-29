#ifndef EXECUTE_H
#define EXECUTE_H

#include "../models.h"

/* This function will execute a built in command, including flags and quoted text */
int execute_command(struct ShellCommand *c);

#endif
