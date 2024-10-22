#ifndef PARSER_H
#define PARSER_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"

# define DQUOTE '\"'
# define SQUOTE '\''

typedef struct s_parse_tree	t_parse_tree;
typedef struct s_redir		t_redir;
typedef struct s_hdoc		t_hdoc;
typedef struct s_job		t_job;
typedef struct s_jobs		t_jobs;

typedef enum	e_type
{
	NONE,
	PIPE,
	EXEC
}	t_type;

struct s_redir
{
	int		in_file;
	int 	out_file;
	char	**files;
	char	*eof;
	char	*args;//inputs
};

struct s_job
{
	char		**args;//quotes
	t_redir		*redir;
	t_job		*next;
};

struct s_jobs
{
	t_type	type;
	t_job	*jobs;
	int		len;
	int		pipe[2];
};

/*
PIPELIST
	- t_job
		- cmd
		- args
		- redirs
	- t_job
		- cmd
		- args
		- redirs
*/

#endif
