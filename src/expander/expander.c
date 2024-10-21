#include "../../inc/minishell.h"

char	*expander_helper(char *prompt, char *addr, char *expansion, char *value)
{
	char	*rtrn;
	char	*temp;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(prompt) - ft_strlen(expansion) + ft_strlen(value);
	rtrn = ft_calloc(1, len + 1);
	if (!rtrn)
		return (NULL);
	i = -1;
	while (prompt[++i] && prompt + i != addr)
		rtrn[i] = prompt[i];
	j = -1;
	while (value[++j])
		rtrn[i + j] = value[j];
	rtrn[i + j] = 0;
	return (rtrn);
}
