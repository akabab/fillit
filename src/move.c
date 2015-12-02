#include "fillit.h"

int		move(int value, t_direction direction)
{
	switch (direction)
	{
		case TOP:
			return (value << 4);
		case LEFT:
			return (value << 1);
		case BOTTOM:
			return (value >> 4);
		case RIGHT:
			return (value >> 1);
		default:
			return (-1);
	}
}