#include <assert.h>

#include "../utils/lexer.h"

int test_lexer() {
	/* First we test a command that is too long */
	char test_string[] = "Hello World!";
	int result = tokenize(test_string);
	assert(result == 0 && "Expected successful reading of string");
	return 0;
}

int main() {
	test_lexer();
	return 0;
}
