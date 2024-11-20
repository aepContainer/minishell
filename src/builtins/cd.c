/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:36 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:32:37 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	cd(t_jobs *jobs, char *path)
{
	if (!path)
	{
		path = env_find_value_const(jobs->env, "HOME");
		if (!path)
			return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		jobs->mshell->quest_mark = 1;
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
