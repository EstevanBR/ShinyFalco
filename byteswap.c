#include <stdio.h>
#include <inttypes.h>

uint8_t* byteSwap(uint8_t*, size_t size) {
	bool centered = (size & 1 == 0);
	int bit_offset;
	int other_offset;
	for (size_t i = 0; i < size; i ++) {
		bit_offset = i*8;
		other_offset = (size-i) * 8;

	}
}

int main(int argc, char const *argv[])
{
	;
	return 69;
}
