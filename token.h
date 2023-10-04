#include <stdio.h>
#include <stdlib.h>

// Consume UTF-8 encoded Unicode Byte Order Mark, if present in the stream
void freadUtf8BOM(FILE* file);

// Returns a token from the stream.
// If EOF is reached, returns NULL.
char *freadtoken(char *buffer, size_t buff_size, FILE *file);
