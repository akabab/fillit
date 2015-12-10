#include <stdlib.h>
#include "libft.h"
#include "fillit.h"

void	fillit_error_msg_exit(char *message)
{
	if (FILLIT_DEBUG)
	{
		if (message)
			ft_putendl_fd(message, 2);
	}
	else
		ft_putendl_fd("error", 2);
	exit(-1);
}
