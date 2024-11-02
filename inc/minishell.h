#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"

# define PROMPT "shellshock <(^_^)> "

// Executor
char	executor(t_mshell *mshell);
char	**accessor(t_mshell *mshell);

#endif
