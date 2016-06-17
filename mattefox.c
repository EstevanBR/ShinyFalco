#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_COSTUMES 4
#define DEFAULT_NUMBER_OF_JACKET_MATERIALS 8
uint16_t byteSwapper(uint16_t);
int main(int argc, char const *argv[])
{
	puts("EDITING FOX");
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
		printf("offset: %#X\n", arrayOfJacketOffsets[i]);
	}

	puts("\nEnter number corresponding to choice:");
	for (int i = 0; i < DEFAULT_NUMBER_OF_COSTUMES; i++) {
		printf("%d: %s\n", i, falcoDATs[i]);
	}
	int choice;
	char fileName[255];
	scanf("%d", &choice);
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

		for (int i = 0; i < DEFAULT_NUMBER_OF_JACKET_MATERIALS; i++) {
			long offset = arrayOfJacketOffsets[i];
			printf("\n%d offset: %#X", i, offset);
			printf("\narrayOfJacketOffsets[i]: %#X", arrayOfJacketOffsets[i]);
			uint16_t jacket;
			fseek(fp, offset, SEEK_SET);
			fread(&jacket, sizeof(uint16_t), 1, fp);
			jacket = byteSwapper(jacket);
			if (jacket == 0x001C) {
				printf("\nmaking the jacket matte");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x14;
			} else if (jacket == 0x0014) {
				printf("\nmaking the jacket shiny");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x1C;
			} else {
				printf("\nERROR!");
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

uint16_t byteSwapper(uint16_t bananas) {
	//this function takes a 2 byte unsigned int,
	//and returns a new 2 byte int,
	//with the first byte swapped with the last byte
	/*
	so:
		before: 0x2468
		after:  0x6824
	*/
	return ((bananas & 0xFF00) >> 8) | ((bananas & 0x00FF) << 8);

}