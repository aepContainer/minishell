#include "../../inc/parser.h"

static void update_quote_state(t_parser_state *state, char c)
{
    if (!state->in_quote)
    {
        state->quote_type = c;
        state->in_quote = true;
    }
    else if (c == state->quote_type)
        state->in_quote = false;
}

static int get_word_len(const char *prompt, t_parser_state *state)
{
    int len = 0;

    if (prompt[state->pos] == '<' || prompt[state->pos] == '>' || prompt[state->pos] == '|')
	{
		if (prompt[state->pos] != '|' && prompt[state->pos] == prompt[state->pos + 1])
			return (2);
		else
			return (1);
	}
    while (prompt[state->pos + len])
    {
        if (prompt[state->pos + len] == '\'' || prompt[state->pos + len] == '\"')
            update_quote_state(state, prompt[state->pos + len]);
        else if (!state->in_quote && (prompt[state->pos + len] == ' ' || 
                prompt[state->pos + len] == '<' || prompt[state->pos + len] == '>' || 
                prompt[state->pos + len] == '|'))
            break;
        len++;
    }
    return (len);
}

static char *get_word(const char *prompt, t_parser_state *state, char **tokens, int current)
{
    char *word;
    int i = 0;

    while (prompt[state->pos] && (prompt[state->pos] == ' ' || prompt[state->pos] == '\t' || 
           prompt[state->pos] == '\v' || prompt[state->pos] == '\f' || prompt[state->pos] == '\r'))
        state->pos++;
    if (!prompt[state->pos])
        return NULL;
    state->len = get_word_len(prompt, state);
	word = ft_calloc(1, state->len + 1);
    if (!word)
        return NULL;
    while (i < state->len)
        word[i++] = prompt[state->pos++];
    word[i] = '\0';
    return (word);
}

char **word_split(char *prompt)
{
    t_parser_state state = {false, 0, 0, 0};
    char **words;
    int word_count = 0;
    int current = 0;
    char *word;

	words = NULL;
    while (prompt[state.pos])
    {
		word = get_word(prompt, &state, words, current);
        if (!word)
            break;
		words = str_arr_realloc(words, word);
		free(word);
		if (!words)
			return (NULL);
    }
    return (words);
}