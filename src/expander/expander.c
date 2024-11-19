#include "../../inc/minishell.h"

void	expander(t_jobs *jobs, char **prompt)
{
    char	*expanded;

    if (!*prompt)
        return ;
    expanded = expand_env_vars(jobs, *prompt);
    if (!expanded)
        return ;
    free(*prompt);
    *prompt = expanded;
}
