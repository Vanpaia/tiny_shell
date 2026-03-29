#ifndef PARSER_H
#define PARSER_H

#include "../config.h"
#include "../models.h"

/* This function will parse the user input for commands, flags, and others */
int parse_user_input(struct ShellCommand *c);

#endif
