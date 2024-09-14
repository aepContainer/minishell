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

static void	get_node_content(t_node *node, char *prompt)
{
	if (node->type == CMD)
		node->content.cmd = prompt;
	if (node->type == ARG)
		add_arg(&node->content.args, prompt);
	if (node->type == PIPE)
		node->content.pipe = 1;
	if (node->type == HDOC)
		node->content.heredoc = 1;
	if (node->type == ENVAR)
		node->content.envar = prompt;
}

static t_node	*tokenize(char *prompt)
{
	t_node	*rtrn;
	t_node	*temp;
	char	**splitted;
	int		i;

	rtrn = ft_calloc(1, sizeof(t_node));
	if (!rtrn)
		return (NULL);
	temp = rtrn;
	splitted = ft_split(prompt, ' ');
	if (!splitted)
		return (free(rtrn), NULL);
	rtrn->type = lexer(splitted[0]);
	i = 0;
	while (splitted[++i])
	{
		temp->next = ft_calloc(1, sizeof(t_node));
		if (!temp->next)
			return (free_args(splitted), free_node(rtrn), NULL);
		temp->next->type = lexer(splitted[i]);
		temp = temp->next;
		get_node_content(temp, prompt);
	}
	return (free_args(splitted), rtrn);
}

t_tree	*parser(t_mshell *mshell)
{
	t_tree	*rtrn;
	t_node	*input_list;

	if (ctrl_quote(mshell->prompt))
		return (NULL);// ErrorPrint!
	input_list = tokenize(mshell->prompt);
	if (check_rules(input_list))// iki pipe || böyle yanyana gelmez! vs.
		return (free_node(input_list), NULL);// ErrorPrint!
	rtrn = ft_calloc(1, sizeof(t_tree));
	if (!rtrn)
		return (NULL);// ErrorPrint!
	if (add_node_to_tree(mshell, rtrn, input_list))
		return (free_tree(rtrn), free_node(input_list), NULL);// ErrorPrint!
	if (inject_jobs(rtrn, input_list))
		return (free_tree(rtrn), free_node(input_list), NULL);// ErrorPrint!
}
