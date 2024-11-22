/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:53 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/22 11:03:09 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_nec(t_mshell *mshell)
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
	mshell->jobs->job_list = NULL;
}

void	free_str_arr_null(char ***arr)
{
	free_str_arr(*arr);
	*arr = NULL;
}

void	free_env(t_env *env)
{
	free_str_arr_null(&env->key);
	free_str_arr_null(&env->value);
	free(env);
}
