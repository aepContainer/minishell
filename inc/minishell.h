#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "dirent.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "termios.h"
# include "signal.h"

# define PROMPT "shellshock <(^_^)> "

// Executor
char	executor(t_mshell *mshell);
char	**accessor(t_mshell *mshell);

// Builtins
char	pwd(void);
char	cd(char *path);

#endif
