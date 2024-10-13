/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:41:48 by apalaz            #+#    #+#             */
/*   Updated: 2024/10/05 23:27:46 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/parser.h"
# include "stdlib.h"
# include "unistd.h"
# include "sys/wait.h"
# include "readline/readline.h"
# include "readline/history.h"

# define PROMPT "shellshock <(^_^)> "

typedef struct s_mshell
{
	char	*prompt;
	char	**envar;
	char	**history;
	t_tree	*tree;
}	t_mshell;

void	print_parse_tree(t_tree *tree, char choice);

char	executor(t_tree *tree);

void	free_mshell(t_mshell *mshell);
void	free_node(t_node *node_list);
void	free_tree(t_tree *tree);
void	free_args(char **args);
char	pwd(void);

#endif
