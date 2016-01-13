
#include <stdlib.h>
#include "libft.h"
#include "fillit.h"

void	fillit_error_msg_exit(char *message)
{
	if (message && FILLIT_DEBUG)
	{
		ft_putstr_fd("Err: ", 1);
		ft_putendl_fd(message, 1);
	}
	else
		ft_putendl_fd("error", 1);
	exit(-1);
}
