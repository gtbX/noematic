#include "token.h"
#include <string.h>

void freadUtf8BOM(FILE* file) {
	static const unsigned char BOM[] = { (char)0xEF, (char)0xBB, (char)0xBF };
	const unsigned char* bom = BOM;
	int c = fgetc(file);
	for (; c != EOF; c = fgetc(file)) {
		if (c != *bom++) {
			ungetc(c, file);
			break;
		}
		if (bom >= BOM + sizeof(BOM)) {
			break;
		}
	}
}

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
