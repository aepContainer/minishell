#include "../../inc/parser.h"

void	process_env_vars(t_env *env, char **prompt)
{
    char	*expanded;

    if (!prompt || !*prompt || !env)
        return ;
    expanded = expand_env_vars(env, *prompt);
    if (!expanded)
        return ;
    free(*prompt);
    *prompt = expanded;
}
