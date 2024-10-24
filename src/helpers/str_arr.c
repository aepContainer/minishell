#include "../../inc/minishell.h"

int	str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**str_arr_realloc(char **arr, char *element)
{
	char	**rtrn;
	int		i;

	if (!arr)
	{
		rtrn = ft_calloc(sizeof(char *), 2);
		if (!rtrn)
			return (NULL);
		rtrn[0] = ft_strdup(element);
		return (free(element),rtrn);
	}
	rtrn = ft_calloc(sizeof(char *), str_arr_len(arr) + 2);
	if (!rtrn)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		rtrn[i] = ft_strdup(arr[i]);
		free(arr[i]);
	}
	rtrn[i] = ft_strdup(element);
	return (free(arr), free(element), rtrn);
}

typedef struct s_parser_state {
    bool in_quote;
    char quote_type;
    int pos;
    int len;
} t_parser_state;

static void skip_spaces(const char *str, int *i)
{
    while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || 
           str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r'))
        (*i)++;
}

static bool is_operator(char c)
{
    return (c == '<' || c == '>' || c == '|');
}

static int get_token_length(const char *input, t_parser_state *state)
{
    int len = 0;
    
    if (is_operator(input[state->pos]))
    {
        len = (input[state->pos] == input[state->pos + 1]) ? 2 : 1;
        return len;
    }
    
    while (input[state->pos + len])
    {
        if (input[state->pos + len] == '\'' || input[state->pos + len] == '\"')
        {
            if (!state->in_quote)
            {
                state->quote_type = input[state->pos + len];
                state->in_quote = true;
            }
            else if (input[state->pos + len] == state->quote_type)
                state->in_quote = false;
        }
        else if (!state->in_quote && (input[state->pos + len] == ' ' || 
                 is_operator(input[state->pos + len])))
            break;
        len++;
    }
    return len;
}

static char *extract_token(const char *input, int start, int len)
{
    char *token = malloc(len + 1);
    int i = 0;
    
    if (!token)
        return NULL;
    while (i < len)
    {
        token[i] = input[start + i];
        i++;
    }
    token[i] = '\0';
    return token;
}

static void cleanup_tokens(char **tokens, int count)
{
    while (count--)
        free(tokens[count]);
    free(tokens);
}

static int count_tokens(const char *input)
{
    t_parser_state state = {false, 0, 0, 0};
    int count = 0;
    
    while (input[state.pos])
    {
        skip_spaces(input, &state.pos);
        if (!input[state.pos])
            break;
        
        state.len = get_token_length(input, &state);
        if (state.len > 0)
            count++;
        
        state.pos += state.len;
    }
    return count;
}

char **get_token(char *input)
{
    if (!input)
        return NULL;
    t_parser_state state = {false, 0, 0, 0};
    int token_count = count_tokens(input);
    char **tokens = malloc(sizeof(char *) * (token_count + 1));
    int current_token = 0;
    
    if (!tokens)
        return NULL;
        
    while (input[state.pos])
    {
        skip_spaces(input, &state.pos);
        if (!input[state.pos])
            break;
            
        state.len = get_token_length(input, &state);
        if (state.len > 0)
        {
            tokens[current_token] = extract_token(input, state.pos, state.len);
            if (!tokens[current_token])
            {
                cleanup_tokens(tokens, current_token);
                return NULL;
            }
            current_token++;
        }
        state.pos += state.len;
    }
    tokens[current_token] = NULL;
    return (tokens);
}
