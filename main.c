#include <stdio.h>
#include <stdlib.h>

#include "token.h"

int main(int argc, char** argv) {
	FILE* f;
	char buffer[128];

	if (argc < 2) {
		printf("Usage: %s [game.dlg]\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		perror("Game file");
		return errno;
	}

	freadtoken(buffer, sizeof(buffer), f);

	printf("%s\n", buffer);

	fclose(f);
	return 0;
}