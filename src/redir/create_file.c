#include "../../inc/parser.h"

void	create_files(char **files, int len)
{
	int	fd;
	int	i;

	i = -1;
	while (++i < len)
	{
		fd = open(files[i], O_CREAT);
		if (fd == -1)
			continue ;
		close(fd);
	}
}
