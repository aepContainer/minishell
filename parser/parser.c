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

static t_node	*new_token(char *input, char type)
{
	t_node	*rtrn;

	if (type == -1)
		return (NULL);
	rtrn = ft_calloc(1, sizeof(t_node));
	if (!rtrn)
		return (NULL);
	rtrn->type = type;
	if (rtrn->type == CMD)
		rtrn->content.cmd = input;
	else if (rtrn->type == ARG)
		add_arg(&rtrn->content.args, input);
//	yapıdaki değerlere değer atamaya devam et!
	if (ft_strnstr(input, "|", ft_strlen(input)))
		rtrn->content.pipe = 1;
	return (rtrn);
}

static t_node	*tokenize(t_parse_tree *rtrn, char *prompt)
{}

t_parse_tree	*parser(t_mshell *mshell)
{
	t_parse_tree	*rtrn;
	t_node			*input_list;
	int				i;

	if (ctrl_quote(mshell->prompt))
		return (NULL);// ErrorPrint!
	rtrn = ft_calloc(1, sizeof(t_parse_tree));
	if (!rtrn)
		return (NULL);
	input_list = tokenize(rtrn, mshell->prompt);
}
