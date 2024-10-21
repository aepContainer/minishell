#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"

typedef struct s_mshell
{
	char	*env;
	t_jobs	*jobs;
}	t_mshell;

#endif
