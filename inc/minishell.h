#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "dirent.h"
# include "unistd.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "stdbool.h"
# include "stdio.h"

# define PROMPT "Shell Shock <_>"

typedef struct s_mshell
{
	char	*prompt;
	char	*env;
	t_jobs	*jobs;
}	t_mshell;

// Builtins
char	pwd(void);

// Helpers
char	**str_arr_realloc(char **arr, char *element);


#endif
