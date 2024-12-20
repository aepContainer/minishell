/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:10 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:41:48 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_word_len(t_parser_state *parser, char *prompt)
{
	int	len;

	if (prompt[parser->i] == '<' || prompt[parser->i] == '>'
		|| prompt[parser->i] == '|')
	{
		if (prompt[parser->i] != '|'
			&& prompt[parser->i] == prompt[parser->i + 1])
			return (2);
		else
			return (1);
	}
	len = -1;
	while (prompt[++len + parser->i])
	{
		if (prompt[parser->i + len] == '\'' || prompt[parser->i + len] == '\"')
			update_quote_state(parser->state, prompt[parser->i + len]);
		else if (!parser->state->in_single && !parser->state->in_double
			&& (prompt[parser->i + len] == ' ' || prompt[parser->i + len] == '<'
				|| prompt[parser->i + len] == '>'
				|| prompt[parser->i + len] == '|'))
			break ;
	}
	return (len);
}

static char	*get_word(t_parser_state *parser, char *prompt)
{
	char	*word;
	int		i;

	while (prompt[parser->i] && (prompt[parser->i] == ' '
			|| prompt[parser->i] == '\t' || prompt[parser->i] == '\v'
			|| prompt[parser->i] == '\f' || prompt[parser->i] == '\r'))
		parser->i++;
	if (!prompt[parser->i])
		return (NULL);
	parser->len = get_word_len(parser, prompt);
	word = ft_calloc(1, parser->len + 1);
	if (!word)
		return (NULL);
	i = 0;
	if (!word)
		return (NULL);
	while (i < parser->len)
		word[i++] = prompt[parser->i++];
	word[i] = 0;
	return (word);
}

static char	*get_trimmed(char *word)
{
	char	*trimmed;

	if (word[0] == '\"')
		trimmed = ft_strtrim(word, "\"");
	else if (word[0] == '\'')
		trimmed = ft_strtrim(word, "\'");
	else
		trimmed = ft_strdup(word);
	return (trimmed);
}

char	**word_split(char *prompt)
{
	t_quote_state	quote_state;
	t_parser_state	parser;
	char			**words;
	char			*word;
	char			*trimmed;

	quote_state = (t_quote_state){false, false};
	parser = (t_parser_state){&quote_state, 0, 0};
	words = NULL;
	while (prompt[parser.i])
	{
		word = get_word(&parser, prompt);
		if (!word)
			break ;
		trimmed = get_trimmed(word);
		free(word);
		if (!trimmed)
			return (free_str_arr(words), NULL);
		words = str_arr_realloc(words, trimmed);
		free(trimmed);
		if (!words)
			return (NULL);
	}
	return (words);
}
