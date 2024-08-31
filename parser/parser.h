#ifndef PARSER_H
# define PARSER_H

# define NONE 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define HDOC 4
# define ENVAR 5

# define SCMD 10
# define CCMD 11
# define JOB 12

typedef struct s_ParseTree t_ParseTree;
typedef struct s_node		t_node;

struct s_node
{
	char	type;
};

struct s_ParseTree
{
	char		node_type;// simple_cmd | complex_cmd | job
	t_node		*this_node;
	t_ParseTree	*next;
};

char	lexer(char *str);

#endif
