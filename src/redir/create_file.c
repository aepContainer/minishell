#include "../../inc/minishell.h"

void	create_file(char **files, int len)
{
	int	fd;
	int	i;

	i = 0;
	while (i < len && files[i])
	{
		fd = open(files[i], O_CREAT);
		if (fd == -1)
			continue ;
		close(fd);
		i++;
	}
}
