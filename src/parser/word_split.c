#include "../../inc/minishell.h"

static int get_word_len(t_parser_state *parser, char *prompt)
{
    int	len;

    if (prompt[parser->i] == '<' || prompt[parser->i] == '>' || prompt[parser->i] == '|')
    {
        if (prompt[parser->i] != '|' && prompt[parser->i] == prompt[parser->i + 1])
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
                || prompt[parser->i + len] == '>' || prompt[parser->i + len] == '|'))
            break ;
    }
    return (len);
}

static char *get_word(t_parser_state *parser, char *prompt)
{
    char	*word;
    int		i;

    while (prompt[parser->i] && (prompt[parser->i] == ' ' || prompt[parser->i] == '\t'
            || prompt[parser->i] == '\v' || prompt[parser->i] == '\f' || prompt[parser->i] == '\r'))
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

char **word_split(char *prompt)
{
    t_quote_state	quote_state = {false, false};
    t_parser_state	parser = {&quote_state, 0, 0};
    char			**words;
    char			*word;

    words = NULL;
    while (prompt[parser.i])
    {
        word = get_word(&parser, prompt);
        if (!word)
            break;
        words = str_arr_realloc(words, word);
        if (!words)
            return (NULL);
    }
    return (words);
}
