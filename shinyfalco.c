#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "matstruct.h"

#define DEFAULT_NUMBER_OF_COSTUMES 4
#define DEFAULT_NUMBER_OF_JACKET_MATERIALS 6
uint16_t endiannessSwapper(uint16_t);
int main(int argc, char const *argv[])
{
	puts("EDITING FALCO");
	FILE *fp;
	char const *falcoDATs[DEFAULT_NUMBER_OF_COSTUMES] = {
		"PlFcNr.dat",	// neutral
		"PlFcGr.dat",	// green
		"PlFcRe.dat",	// red
		"PlFcBu.dat"	// blue
	};
	long const arrayOfJacketOffsets[DEFAULT_NUMBER_OF_JACKET_MATERIALS] = {
		0x6FEE,
		0x70AE,
		0x716E,
		0x7D9A,
		0x7E5A,
		0X7F1A
	};

	long const arrayOfMatOffsets[DEFAULT_NUMBER_OF_JACKET_MATERIALS] = {
		0x6FE8,
		0x70A8,
		0x7168,
		0x7D94,
		0x7E54,
		0X7F14
	};

	for (int i = 0; i < DEFAULT_NUMBER_OF_JACKET_MATERIALS; i++) {
		printf("offset: %#lx\n", arrayOfJacketOffsets[i]);
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

		for (int i = 0; i < DEFAULT_NUMBER_OF_JACKET_MATERIALS; i++) {			
			matstruct mat;
			long matOffset = arrayOfMatOffsets[i];
			fseek (fp, matOffset, SEEK_SET);
			fread(&mat, sizeof(mat), 1, fp);
			printf("\nunknown value: %#.04x", endiannessSwapper(mat.unknownValue));
			
			long offset = arrayOfJacketOffsets[i];
			uint16_t jacket;
			fseek(fp, offset, SEEK_SET);
			fread(&jacket, sizeof(uint16_t), 1, fp);
			jacket = endiannessSwapper(jacket);
			if (jacket == 0x001c) {
				printf("\nmaking the jacket matte");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x14;
			} else if (jacket == 0x0014) {
				printf("\nmaking the jacket shiny");
				BUFFER[offset] = 0x00;
				BUFFER[offset+1] = 0x1c;
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

uint16_t endiannessSwapper(uint16_t bananas) {
	//this function takes a 2 byte unsigned int,
	//and returns a new 2 byte int,
	//with the first byte swapped with the last byte
	/*
	so:
		before: 0x2468
		after:  0x6824
	*/
	return ((bananas & 0xff00) >> 8) | ((bananas & 0x00ff) << 8);

}