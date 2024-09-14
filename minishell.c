/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:41:44 by apalaz            #+#    #+#             */
/*   Updated: 2024/08/19 16:42:15 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_tree		*parsed;
	t_mshell	*mshell;
	char		*prompt;

	prompt = get_prompt();
	if (!prompt)
		return (-1);// ErrorPrint!
	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (free(prompt), -1);// ErrorPrint!
	parsed = parser(mshell);
	if (!parsed)
		return (free_mshell(mshell), free(prompt), -1);// ErrorPrint!
	executor(parsed);
	return (0);
}
