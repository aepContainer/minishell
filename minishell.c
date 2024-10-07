/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:41:44 by apalaz            #+#    #+#             */
/*   Updated: 2024/09/25 16:40:46 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ctrl_builtins(char	*prompt)
{
	if (!ft_strncmp(prompt, "pwd", ft_strlen(prompt))
			&& ft_strlen(prompt) == 3)
		return (pwd());
	return (-1);
}

static char	*read_prompt(void)
{
	char	*rtrn;

	rtrn = readline(PROMPT);
	if (!rtrn)
		return (NULL);
	while (!*rtrn)
	{
		rtrn = readline(PROMPT);
		if (!rtrn)
			return (NULL);
	}
	return (add_history(rtrn), rtrn);
}

char	process(t_mshell *mshell)
{
	mshell->prompt = read_prompt();
	if (!mshell->prompt)
		return (-1);
	//parser(mshell);
	if (ctrl_builtins(mshell->prompt))
		return (-1);
	//executor(mshell);
	return (free(mshell->prompt), 0);
}

int main(void)
{
	t_mshell	*mshell;
	//char		**envp;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (-1);
	while (1)
		if (process(mshell))
			break ;
	//quitting(mshell);
	return (0);
}
