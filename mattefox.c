#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_COSTUMES 4
#define DEFAULT_NUMBER_OF_JACKET_MATERIALS 8
uint16_t bitOfWork(uint16_t);
int main(int argc, char const *argv[])
{
	puts("EDITING FOX");
	/* code */
	FILE *fp;
	char const *falcoDATs[DEFAULT_NUMBER_OF_COSTUMES] = {
		"PlFxNr.dat",	// neutral
		"PlFxGr.dat",	// green
		"PlFxOr.dat",	// orange
		"PlFxLa.dat"	// blue
	};
	long const arrayOfJacketOffsets[DEFAULT_NUMBER_OF_JACKET_MATERIALS] = {
		0x9952,
		0x9A12,
		0x9B92,
		0x9C52,
		0xB072,
		0xB132,
		0xB1F2,
		0xB2B2
	};
	for (int i = 0; i < DEFAULT_NUMBER_OF_JACKET_MATERIALS; i++) {
		printf("offset: %ld\n", arrayOfJacketOffsets[i]);
	}

	puts("\nEnter number corresponding to choice:");
	for (int i = 0; i < DEFAULT_NUMBER_OF_COSTUMES; i++) {
		printf("%d: %s\n", i, falcoDATs[i]);
	}
	uint8_t choice;
	char fileName[255];
	scanf("%" SCNu8, &choice);
	if (choice >= 0 && choice < DEFAULT_NUMBER_OF_COSTUMES) {
		strcpy(fileName, falcoDATs[choice]);
		printf("You chose: %s\n", fileName);
	} else {
		puts("invalid choice \007");
		return -1;
	}

	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		puts("failed to open file \007");
		return -1;
	} else {
		puts("succesfully opened file");
		fseek(fp,0,SEEK_END);
		long file_size = ftell(fp);
		printf("size of file is : %ld\n", file_size);

		uint8_t BUFFER[file_size];
		fseek(fp, 0, SEEK_SET);
		fread(BUFFER, sizeof(uint8_t), file_size, fp);
		// for (int i = 0; i<500;i++) {
		// 	printf("%.02" PRIX8, BUFFER[i]);
		// 	if (i % 2 == 0) {
		// 		printf(" ");
		// 	}
		// 	if (i % 32 == 0) {
		// 		printf("\n");
		// 	}
		// }

		for (int i = 0; i < DEFAULT_NUMBER_OF_JACKET_MATERIALS; i++) {
			long offset = arrayOfJacketOffsets[i];
			uint16_t jacket;
			fseek(fp, offset, SEEK_SET);
			fread(&jacket, sizeof(uint16_t), 1, fp);
			jacket = bitOfWork(jacket);
			if (jacket == 0x001C) {
				printf("\nmaking the jacket matte");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x14;
			} else if (jacket == 0x0014) {
				printf("\nmaking the jacket shiny");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x1C;
			} else {
				printf("ERROR!");
			}
			printf("\nwas: %#0.2x ::", jacket);
			printf("is:  %#0.2x\n", BUFFER[offset+1]);
		}
		FILE *fpout;
		char* outFileName = fileName;
		strcat(outFileName, ".out");
		printf("\nOutputted to: \"%s\"\nYou will need to delete \".out\" before importing", outFileName);
		fpout = fopen(outFileName, "wb");
		fwrite(BUFFER, sizeof(uint8_t), file_size, fpout);
		fclose(fpout);
	}

	puts("\nClosing file...");
	fclose(fp);
	return 0;
}

uint16_t bitOfWork(uint16_t bananas) {
	return ((bananas & 0xFF00) >> 8) | ((bananas & 0x00FF) << 8);

}