/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:05 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:06 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	pwd(t_jobs *jobs)
{
	char	wd[512];

	if (!getcwd(wd, 512))
	{
		jobs->mshell->quest_mark = 1;
		perror("pwd");
		return (EXIT_FAILURE);
	}
	write(1, wd, ft_strlen(wd));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
