// -------------------------------------------------------------
// Material Structures
// -------------------------------------------------------------
// Offset	Size	Format		Description
// -------------------------------------------------------------
// 0x00		4		pointer		String Offset (typically unused)
// 0x04		2		unsigned	Unknown Flags
// 0x06		2		unsigned	Unknown Value
// 0x08		4		pointer		Texture Struct Offset
// 0x0C		4		pointer		Colors Struct Offset
// 0x10		4		unsigned	Unknown
// 0x14		4		pointer		Unknown (to struct of size 0x0C)
// -------------------------------------------------------------

#include <stdio.h>
#include <inttypes.h>

struct MaterialStruct
{
	uint32_t stringOffset;
	uint16_t unknownFlags;
	uint16_t unknownValue;
	uint32_t textureStructOffset;
	uint32_t colorsStructOffset;
	uint32_t unknownPointer1;
	uint32_t unknownPointer2;
};
typedef struct MaterialStruct MaterialStruct;

int main(int argc, char const *argv[])
{
	return 0;
}