/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:41:48 by apalaz            #+#    #+#             */
/*   Updated: 2024/08/30 19:14:50 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell >> "

typedef struct s_mshell
{
	char		**envar;
	char		**history;
	ParseTree	*parsed;
}	t_mshell;

void	free_and_exit(t_mshell *mshell);

#endif
