#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {
	int state = 1;
	char *line = NULL;
	size_t size = 0;
	char command[256];
	int argument_no = 0;

	while (state == 1) {
		printf("marginella> ");
		command[0] = '\0';
		ssize_t len = getline(&line, &size, stdin);
		line[strcspn(line, "\n")] = '\0';
		char * pch;
		pch = strtok (line," ");
		while (pch != NULL)
		{
			if (command[0] == '\0') {
				printf ("Command: %s\n",pch);
				strcpy(command, pch);
				pch = strtok (NULL, " ");
			} else if (pch[0] == '-') {
				printf ("Argument: %s\n",pch);
				pch = strtok (NULL, " ");
				argument_no ++;
			} else {
				printf ("Extra: %s\n",pch);
				pch = strtok (NULL, " ");
			}
		}

		printf("Number of arguments: %i\n", argument_no);
		argument_no = 0;
		if (strcmp(line, "exit") == 0) {
			free(line);
			state = 0;
			return 0;
		}
	}
}
