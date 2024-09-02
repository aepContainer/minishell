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

# include "parser/parser.h"
# include "error/error.h"
# include "stdlib.h"
# include "unistd.h"

# define PROMPT "minishell >> "

typedef struct s_mshell
{
	char	*prompt;
	char	**envar;
	char	**history;
	char	nop;// number of pipe
	t_tree	*parsed;
}	t_mshell;

void	free_mshell(t_mshell *mshell);

#endif
