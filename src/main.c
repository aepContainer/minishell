/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:36 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/22 00:30:41 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	nuller(t_mshell *mshell)
{
	t_job	*temp;
	t_job	*next;

	temp = mshell->jobs->job_list;
	while (temp)
	{
		next = temp->next_job;
		free_job_list(temp);
		temp = next;
	}
	mshell->jobs->job_list = ft_calloc(1, sizeof(t_job));
	if (!mshell->jobs->job_list)
		return (EXIT_FAILURE);
	mshell->jobs->job_list->redir = ft_calloc(1, sizeof(t_redir));
	if (!mshell->jobs->job_list->redir)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_mshell	*mshell_init(char **env)
{
	t_mshell	*mshell;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	if (!mshell->jobs)
		return (free(mshell), NULL);
	if (get_first_env(mshell->jobs, env))
		return (free(mshell->jobs), free(mshell), NULL);
	mshell->jobs->mshell = mshell;
	return (mshell);
}

static char	process(t_mshell *mshell, char *prompt)
{
	t_job	*temp;

	if (parser(mshell->jobs, prompt))
		return (EXIT_FAILURE);
	temp = mshell->jobs->job_list;
	while (temp)
	{
		if (!temp->args)
		{
			ft_putendl_fd("Syntax error special char got used as a command.",
				2);
			mshell->quest_mark = 2;
			return (EXIT_FAILURE);
		}
		temp = temp->next_job;
	}
	if (executor(mshell))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	start_mshell(t_mshell *mshell)
{
	char	*prompt;
	char	*trim;

	while (1)
	{
		set_signal(MAIN);
		prompt = readline(PROMPT);
		if (!prompt)
			break ;
		trim = ft_strtrim(prompt, " \t\r\f\v");
		free(prompt);
		if (!trim)
			break ;
		set_signal(314);
		if (nuller(mshell))
		{
			free(trim);
			break ;
		}
		if (process(mshell, trim))
			continue ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;

	(void)argv;
	if (argc != 1)
		return (1);
	mshell = mshell_init(env);
	if (!mshell)
		return (EXIT_FAILURE);
	start_mshell(mshell);
	free_mshell(mshell);
	return (0);
}
