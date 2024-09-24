#ifndef MSHELL_H
# define MSHELL_H

# include "../libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "unistd.h"
# include "fcntl.h"
# include "errno.h"
# include "utmp.h"
# include "stdio.h"
# include "signal.h"
# include "dirent.h"

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
