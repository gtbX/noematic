#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	FILE* f;
	if (argc < 2) {
		printf("Usage: %s [game.dlg]\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		perror("Game file");
		return errno;
	}

	fclose(f);
	return 0;
}