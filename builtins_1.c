#include "mshell.h"

char	pwd(void)
{
	char	rtrn[512];

	ft_bzero(rtrn, 512);
	if (!getcwd(rtrn, 512))
		return (-1);
	write(1, rtrn, ft_strlen(rtrn));
	write(1, "\n", 1);
	return (0);
}
