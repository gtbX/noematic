#include "token.h"
#include <string.h>

char *freadtoken(char *buffer, size_t buff_size, FILE *file) {
	int i, c;
	const char *whitespace = "=;() \"\t\f\r\v\n";

	while( strchr( whitespace, (char)(c= fgetc( file )) ) != NULL );
	if( c == EOF )
		return NULL;
	for( i = 0; i < buff_size -1; i++ ){
		buffer[i] = c;
		if( strchr( whitespace, (char)(c= fgetc( file )) ) != NULL ){
			buffer[i+1] = '\0';
			break;
		}
	}
	buffer[buff_size-1]= '\0';
	return buffer;
}
