#include "../../inc/minishell.h"

typedef struct s_quote_state
{
    bool in_single;
    bool in_double;
}   t_quote_state;

char *expander_helper(char *prompt, char *addr, char *expansion, char *value)
{
    char    *rtrn;
    int     len;
    int     i;
    int     j;

    len = ft_strlen(prompt) - ft_strlen(expansion) + ft_strlen(value);
    rtrn = ft_calloc(1, len + 1);
    if (!rtrn)
        return (NULL);
    i = -1;
    while (prompt[++i] && prompt + i != addr)
        rtrn[i] = prompt[i];
    j = -1;
    while (value[++j])
        rtrn[i + j] = value[j];
    rtrn[i + j] = 0;
    return (rtrn);
}

static void update_quote_state(char c, t_quote_state *state)
{
    if (c == '\'' && !state->in_double)
        state->in_single = !state->in_single;
    else if (c == '\"' && !state->in_single)
        state->in_double = !state->in_double;
}

static char *find_env_value(t_env *env, const char *key, size_t key_len)
{
    if (!key || key_len == 0 || !env)
        return (NULL);
    while (env)
    {
        if (ft_strlen(env->key) == key_len &&
            !ft_strncmp(env->key, key, key_len))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

static size_t get_var_length(const char *str, size_t *i, t_env *env)
{
    size_t  var_start;
    char    *value;
    size_t  len;

    (*i)++;
    var_start = *i;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    if (var_start < *i)
    {
        value = find_env_value(env, str + var_start, *i - var_start);
        return (value ? ft_strlen(value) : 0);
    }
    return (1);
}

static size_t calculate_expanded_length(const char *str, t_env *env)
{
    size_t  len;
    size_t  i;
    t_quote_state state;
    
    len = 0;
    i = 0;
    state.in_single = false;
    state.in_double = false;
    while (str[i])
    {
        update_quote_state(str[i], &state);
        if (str[i] == '$' && !state.in_single)
            len += get_var_length(str, &i, env);
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

static void copy_var_value(const char *input, size_t *i, size_t *j,
                        	char *result, t_env *env, size_t total_len)
{
    size_t  var_start;
    char    *value;

    (*i)++;
    var_start = *i;
    while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
        (*i)++;
    if (var_start < *i)
    {
        value = find_env_value(env, input + var_start, *i - var_start);
        if (value)
        {
            ft_strlcpy(result + *j, value, total_len - *j + 1);
            *j += ft_strlen(value);
        }
    }
    else
        result[(*j)++] = '$';
}

char *expand_env_variables(const char *input, t_env *env)
{
    size_t total_len;
    char *result;
    size_t i;
    size_t j;
    t_quote_state state;

    if (!input)
        return (NULL);
    total_len = calculate_expanded_length(input, env);
    result = (char *)malloc(total_len + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    state = (t_quote_state){false, false};
    while (input[i])
    {
        update_quote_state(input[i], &state);
        if (input[i] == '$' && !state.in_single)
            copy_var_value(input, &i, &j, result, env, total_len);
        else
            result[j++] = input[i++];
    }
    result[j] = '\0';
    return (result);
}

void process_env_vars(char **input, t_env *env)
{
    char *expanded;

    if (!input || !*input || !env)
        return ;
    expanded = expand_env_variables(*input, env);
    if (!expanded)
        return ;
    free(*input);
    *input = expanded;
}
