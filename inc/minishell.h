#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "dirent.h"
# include "readline/readline.h"
# include "readline/history.h"

# define PROMPT "Shell Shock <_>"

// Builtins
char	pwd(void);

// Helpers
char	**str_arr_realloc(char **arr, char *element);


#endif
