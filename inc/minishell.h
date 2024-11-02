#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"

# define PROMPT "shellshock <(^_^)> "

// Executor
char	executor(t_mshell *mshell);
char	**accessor(t_mshell *mshell);

// Builtins
char	ctrl_builtins(char	*prompt);
char	export(t_env **env, char *key, char *value, char *arg);
char	pwd(void);
char	cd(char *path);

#endif
