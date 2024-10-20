#include "parser.h"

static char	distribute_jobs(t_tree *tree, char *prompt)
{
	int	job_i;
	int	i;

	job_i = 0;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] != '|')
		{
			tree->jobs[job_i] = ft_calloc(1, sizeof(t_jobs));
			if (!tree->jobs[job_i])
				return (free_jobs(tree->jobs), -1);
			if (inject_char_to_str(&tree->jobs[job_i]->job, prompt[i]))
				return (-1);
		}
		else
		{
			job_i++;
			i++;
		}
	}
	return (0);
}

static char	pipe_ctrl(t_tree *tree, char *prompt)
{
	int	i;

	tree->noj = 1;
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '|')
			tree->noj++;
	tree->jobs = ft_calloc(sizeof(t_jobs *), tree->noj + 1);
	if (!tree->jobs)
		return (-1);
	return (distribute_jobs(tree, prompt));
}

static char	quote_nbr_ctrl(t_tree *tree)
{
	char	nbr_of_q;
	int		i;
	int		j;

	nbr_of_q = 0;
	i = -1;
	if (tree->jobs[i]->job[0] && (tree->jobs[i]->job[0] == DQUOTE
			|| tree->jobs[i]->job[0] == SQUOTE))
		return (1);
	while (++i < tree->noj)
	{
		j = -1;
		while (tree->jobs[i]->job[++j])
		{
			if (nbr_of_q == 0 && (tree->jobs[i]->job[j] == SQUOTE
					|| tree->jobs[i]->job[j] == DQUOTE))
				nbr_of_q = tree->jobs[i]->job[j];
			else if (!nbr_of_q && nbr_of_q == tree->jobs[i]->job[j])
				nbr_of_q = 0;
		}
		if (nbr_of_q)
			return (-1);
	}
	return (0);
}

static char	qda_helper(t_tree *tree, int i, int j, char type_quote)
{
	char	*temp;
	char	other_quote;
	int		k;

	if (type_quote == SQUOTE)
		other_quote = DQUOTE;
	else
		other_quote = SQUOTE;
	k = ft_strlen(tree->jobs[i]->job);
	while (--k >= 0)
	{
		if (tree->jobs[i]->job[k] == other_quote)
			return (-1);
		if (tree->jobs[i]->job[k] == type_quote)
		{
			temp = ft_substr(tree->jobs[i]->job, j, k);
			if (!temp)
				return (-1);
			inject_str_to_arr(&tree->jobs[i]->elements->args, temp);
			return (k);
		}
	}
	return (-1);
}

static char	quote_distribute_args(t_tree *tree)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (tree->jobs[++i])
	{
		j = -1;
		while (tree->jobs[i]->job[++j])
		{
			if (tree->jobs[i]->job[j] == SQUOTE)
			{
				k = qda_helper(tree, i, j, SQUOTE);
				j = k;
			}
			else if (tree->jobs[i]->job[j] == DQUOTE)
			{
				k = qda_helper(tree, i, j, DQUOTE);
				j = k;
			}
			if (k == -1)
				return (-1);
		}
	}
	return (0);
}

static char	distribute_other1(t_tree *tree)
{
	char	*env;
	int		c_len;
	int		p_len;

	env = getenv("PATH");
    tree->env = ft_split(env, ':');
	free(env);
	if (!tree->env)
		return (-1);
	p_len = str_arr_len(tree->env);
    c_len = str_arr_len(tree->cmds);
    tree->paths = joins(tree->env, p_len, tree->cmds, c_len);
	if (!tree->paths)
		return (-1);
	//if (distribute_other2(tree))
	//	return (-1);
	return (0);
}

char	parser(t_tree *tree, char *prompt)
{
	if (pipe_ctrl(tree, prompt))
		return (-1);
	if (quote_nbr_ctrl(tree))
		return (-1);
	if (initialize_elements(tree))
		return (-1);
	if (quote_distribute_args(tree))
		return (-1);
	return (distribute_other1(tree));
}
