#include <stdio.h>
#include <stdlib.h>

// Returns a token from the stream.
// If EOF is reached, returns NULL.
char *freadtoken(char *buffer, size_t buff_size, FILE *file);
