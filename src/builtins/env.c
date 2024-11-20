/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:51 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:32:52 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env(t_jobs *jobs)
{
	int	i;

	i = -1;
	while (++i < jobs->env->len)
	{
		write(1, jobs->env->key[i], ft_strlen(jobs->env->key[i]));
		write(1, "=", 1);
		write(1, jobs->env->value[i], ft_strlen(jobs->env->value[i]));
		write(1, "\n", 1);
	}
	jobs->mshell->quest_mark = 0;
}
