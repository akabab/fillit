#include "fillit.h"

int		move(int value, int offset)
{
	if (offset < 0)
	{
		printf("move << %d\n", -offset);
		value <<= -offset;
	}
	else
	{
		printf("move >> %d\n", offset);
		value >>= offset;
	}
	return (value);
}