#include "../minishell.h"

static char	ctrl_quote(char *prompt)
{
	char	state;
	int		i;

	state = 0;
	i = -1;
	while (prompt[++i])
	{
		if (!state && (prompt[i] == '\'' || prompt[i] == '\"'))
			state = prompt[i];
		else if (state && (prompt[i] == '\'' || prompt[i] == '\"'))
			state = 0;
	}
	return (state);
}

static t_node	*tokenize(t_tree *rtrn, char *prompt)
{}

t_tree	*parser(t_mshell *mshell)
{
	t_tree	*rtrn;
	t_node			*input_list;
	int				i;

	if (ctrl_quote(mshell->prompt))
		return (NULL);// ErrorPrint!
	rtrn = ft_calloc(1, sizeof(t_tree));
	if (!rtrn)
		return (NULL);
	input_list = tokenize(rtrn, mshell->prompt);
}
