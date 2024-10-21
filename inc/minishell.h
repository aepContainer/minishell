#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "dirent.h"
# include "unistd.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "stdio.h"

# define PROMPT "Shell Shock <_>"

typedef struct s_mshell
{
	char	*prompt;
	char	*env;
	t_jobs	*jobs;
}	t_mshell;

char	pwd(void);

#endif
