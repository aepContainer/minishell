#include "../../inc/parser.h"

char	ctrl_builtins(char	*prompt)
{
	if (!ft_strncmp(prompt, "pwd", 3)
			&& ft_strlen(prompt) == 3)
		return (pwd());
	return (-1);
}
