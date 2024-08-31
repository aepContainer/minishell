#include "../minishell.h"

t_ParseTree	*parser(int argc, char **argv)
{
	t_ParseTree	*rtrn;

	if (!argc)
		return (NULL);
	rtrn = ft_calloc(1, sizeof(t_ParseTree));
	if (!rtrn)
		return (NULL);
}
