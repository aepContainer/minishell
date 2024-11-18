#include "../inc/minishell.h"

static bool	is_special_char(const char *token)
{
    return (ft_strncmp(token, "|", 2) == 0
			|| ft_strncmp(token, "<", 2) == 0
            || ft_strncmp(token, ">", 2) == 0
            || ft_strncmp(token, "<<", 3) == 0
            || ft_strncmp(token, ">>", 3) == 0);
}

bool	check_syntax_errors(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i], "|", 2) == 0)
        {
            if (i == 0 || tokens[i + 1] == NULL || is_special_char(tokens[i + 1]))
            {
                ft_putendl_fd("Syntax error near unexpected token '|'", 2);
                return (true);
            }
        }
        if (is_special_char(tokens[i]) && ft_strncmp(tokens[i], "|", 2) != 0)
        {
            if (tokens[i + 1] == NULL || is_special_char(tokens[i + 1]))
            {
                ft_putendl_fd("Syntax error near unexpected token", 2);
                return (true);
            }
        }
        i++;
    }
    return (false);
}

bool	check_unclosed_quotes(const char *input)
{
    char quote;

	quote = 0;
    while (*input)
    {
        if ((*input == '\'' || *input == '"') && (quote == '\0' || quote == *input))
		{
			if (!quote)
				quote = *input;
			else
				quote = 0;
		}
        input++;
    }
    if (quote)
    {
        ft_putendl_fd("Syntax error: Unclosed quote", 2);
        return (true);
    }
    return (false);
}
