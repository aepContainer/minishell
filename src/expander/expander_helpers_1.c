#include "../../inc/minishell.h"

static int	get_var_length(t_jobs *jobs, char *str, int *i)
{
    char	*value;
    int		var_start;

    (*i)++;
    var_start = *i;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    if (var_start < *i)
    {
        value = find_value(jobs->env, str + var_start, *i - var_start);
		if (value)
			return (ft_strlen(value));
    }
    else if (ft_strncmp(str, "?", 1) && ft_strlen(str) == 1)
    {
        value = ft_itoa(g_quest_mark);
        if (!value)
            return (0);
        return (ft_strlen(value));
    }
    return (0);
}

static int	calculate_expanded_length(t_jobs *jobs, char *str)
{
    t_quote_state	state;
    int				len;
    int				i;

    len = 0;
    i = 0;
    state.in_single = false;
    state.in_double = false;
    while (str[i])
    {
        update_quote_state(&state, str[i]);
        if (str[i] == '$' && !state.in_single)
            len += get_var_length(jobs, str, &i);
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

static char	expand_env_vars_line_helper(t_jobs *jobs, char *prompt, char *result, int *temps)
{
	char	*value;

	temps[0]++;
	temps[3] = temps[0];
	while (prompt[temps[0]] && (ft_isalnum(prompt[temps[0]]) || prompt[temps[0]] == '_'))
		temps[0]++;
	if (temps[3] < temps[0])
	{
		value = find_value(jobs->env, prompt + temps[3], temps[0] - temps[3]);
        if (!value && !ft_strncmp(prompt, "?", 1) && ft_strlen(prompt) == 1)
            value = ft_itoa(g_quest_mark);
		if (value)
		{
			ft_strlcpy(result + temps[1], value, temps[2] - temps[1] + 1);
            temps[1] += ft_strlen(value);
		}
		temps[1] += ft_strlen(value);
	}
	else
		result[temps[1]++] = '$';
	return (EXIT_SUCCESS);
}

static int	*init_temps(t_jobs *jobs, char *prompt)
{
	int	*temps;

	temps = ft_calloc(4, sizeof(int));
	if (!temps)
		return (NULL);
	temps[2] = calculate_expanded_length(jobs, prompt);
	return (temps);
}

char	*expand_env_vars(t_jobs *jobs, char *prompt)
{
    t_quote_state	state = (t_quote_state){false, false};
    char			*result;
    int				*temps;

    if (!prompt)
        return (NULL);
	temps = init_temps(jobs, prompt);
	if (!temps)
		return (NULL);
    result = ft_calloc(1, temps[3] + 1);
    if (!result)
        return (free(temps), NULL);
    while (prompt[temps[0]])
    {
        update_quote_state(&state, prompt[temps[0]]);
        if (prompt[temps[0]] == '$' && !state.in_single)
		{
			if (expand_env_vars_line_helper(jobs, prompt, result, temps))
				return (free(temps), NULL);
		}
        else
            result[temps[1]++] = prompt[temps[0]++];
    }
	result[temps[1]] = 0;
    return (free(temps), result);
}
