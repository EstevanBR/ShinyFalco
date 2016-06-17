#include <stdio.h>
#include <inttypes.h>
#define DEFAULT_NUMBER_OF_COSTUMES 4
int main(int argc, char const *argv[])
{
	/* code */
	FILE *fp;
	char const *falcoDATs[DEFAULT_NUMBER_OF_COSTUMES] = {
		"PlFcNr.dat",	// neutral
		"PlFcGr.dat",	// green
		"PlFcRe.dat",	// red
		"PlFcBu.dat"	// blue
	};

	for (int i = 0; i < DEFAULT_NUMBER_OF_COSTUMES; i++) {
		printf("%s\n", falcoDATs[i]);
	}

	fp = fopen("PlFcGr.dat", "r+");
	long bytes = 243998;
	long arrayOfJacketOffsets = {0x6FEE};
	uint8_t BUFFER[bytes];
	printf("%lu\n", sizeof(BUFFER));
	if (fp == NULL) {
		puts("failed to open file");
		return -1;
	} else {
		puts("succesfully opened file");
		fseek(fp,0,SEEK_END);
		printf("size of file is : %ld\n", ftell(fp));
		fseek(fp,0,SEEK_SET);
		//should be approx 243,998 bytes
		fread(BUFFER, sizeof(uint8_t), bytes, fp);
		for (int i = 0; i <100; i++) {
			if (i % 2 == 0 && i > 0) {
				printf(" ");
			}
			if (i % 16 == 0 && i > 0) {
				printf("\n");
			}
			printf("%.02X" /*PRIu8*/, BUFFER[i]);
		}

		fseek (fp,0x6FEF,SEEK_SET);
		uint16_t jacket;
		printf("\njacket is: %#.02X" /*PRIu8*/, BUFFER[0x6FEF]);

		fseek (fp,0x6FEE,SEEK_SET);
		fscanf(fp, "%" SCNu16, &jacket);
		printf("\nafter fscanf: %" PRIu16,jacket);
	}

	puts("\nclosing file...");
	fclose(fp);
	return 0;
}