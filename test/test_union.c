#include <stdint.h>
#include <stdio.h>

typedef union	u_tetri_value
{
	uint16_t	v[4];
	uint64_t	value;
}				t_tetri_value;

int		main()
{
	t_tetri_value	tv;

	tv.value = -1;
	printf("%llu\n", tv.value);
	printf("%d\n", tv.v[3]);
	return (0);
}