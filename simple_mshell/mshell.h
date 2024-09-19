#ifndef MSHELL_H
# define MSHELL_H

# include "../libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "unistd.h"
# include "stdio.h"

# define PROMPT "shell shock >> "

typedef struct s_mshell
{
	char	*prompt;
	//char	**envar;
	//char	**history;
	//char	nop;// number of pipe
}	t_mshell;

char	pwd(void);

#endif
