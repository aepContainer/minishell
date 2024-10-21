#include "../../inc/minishell.h"

char	cd(char *path)
{
	return (chdir(path));
}
