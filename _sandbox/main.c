#include <stdio.h>
#include <stdlib.h>



# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

int main(int argc, char const *argv[])
{
	/* code */
	printf("COLOR_DISCO : %X\n", COLOR_DISCO);
	printf("COLOR_BRICK_RED : %X\n", COLOR_BRICK_RED);

	// int current = 0.2*COLOR_DISCO + 0.8*COLOR_BRICK_RED;
	int current = COLOR_DISCO + (COLOR_BRICK_RED - COLOR_DISCO) * 0.2;
	printf("current : %X\n", current);
	return 0;
}
