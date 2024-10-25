#include "../../inc/parser.h"

static void update_quote_state(t_parser_state *parser, char c)
{
    if (c == '\'')
    {
        if (!parser->state->in_double)
            parser->state->in_single = !parser->state->in_single;
    }
    else if (c == '\"')
    {
        if (!parser->state->in_single)
            parser->state->in_double = !parser->state->in_double;
    }
}

static int get_word_len(const char *prompt, t_parser_state *parser)
{
    int	len;

    if (prompt[parser->pos] == '<' || prompt[parser->pos] == '>' || prompt[parser->pos] == '|')
    {
        if (prompt[parser->pos] != '|' && prompt[parser->pos] == prompt[parser->pos + 1])
            return (2);
        else
            return (1);
    }
	len = -1;
    while (prompt[++len + parser->pos])
    {
        if (prompt[parser->pos + len] == '\'' || prompt[parser->pos + len] == '\"')
            update_quote_state(parser, prompt[parser->pos + len]);
        else if (!parser->state->in_single && !parser->state->in_double && 
                (prompt[parser->pos + len] == ' ' || prompt[parser->pos + len] == '<' || 
                 prompt[parser->pos + len] == '>' || prompt[parser->pos + len] == '|'))
            break;
    }
    return (len);
}

static char *get_word(const char *prompt, t_parser_state *parser, char **tokens, int current)
{
    char	*word;
    int		i;

    while (prompt[parser->pos] && (prompt[parser->pos] == ' ' || prompt[parser->pos] == '\t' || 
           prompt[parser->pos] == '\v' || prompt[parser->pos] == '\f' || prompt[parser->pos] == '\r'))
        parser->pos++;
    if (!prompt[parser->pos])
        return NULL;
    parser->len = get_word_len(prompt, parser);
    word = ft_calloc(1, parser->len + 1);
    if (!word)
        return NULL;
	i = 0;
    while (i < parser->len)
        word[i++] = prompt[parser->pos++];
    word[i] = '\0';
    return (word);
}

char **word_split(char *prompt)
{
    t_quote_state	quote_state = {false, false};
    t_parser_state	parser = {&quote_state, 0, 0};
    char			**words;
    char			*word;
    
    words = NULL;
    while (prompt[parser.pos])
    {
        word = get_word(prompt, &parser, words, 0);
        if (!word)
            break;
        words = str_arr_realloc(words, word);
        free(word);
        if (!words)
            return (NULL);
    }
    return (words);
}
