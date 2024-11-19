#include "../../inc/minishell.h"
#include "limits.h"

static char	calculate_result(const char *str, int *index, long *result)
{
	while (str[*index] && ft_isdigit(str[*index]))
	{
		if (*result > (LONG_MAX - (str[*index] - '0')) / 10)
			return (EXIT_FAILURE);
		*result = *result * 10 + (str[*index] - '0');
		(*index)++;
	}
	return (EXIT_SUCCESS);
}

static int	get_exit_value(char *str)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = 0;
	if (calculate_result(str, &i, &result))
		return (EXIT_FAILURE);
	result = (result * sign) % 256;
	if (result < 0)
		result += 256;
	return (result);
}

static char	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (EXIT_FAILURE);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	handle_exit_argument(char **args, char *stripped)
{
	int	exit_status;

	if (is_all_digit(stripped))
	{
		exit_error(args[1], "numeric argument required\n");
		free(stripped);
		exit(g_quest_mark);
	}
	if (args[2])
	{
		g_quest_mark = 1;
		write(2, "minishell: exit: too many arguments\n", 37);
		free(stripped);
		return ;
	}
	exit_status = get_exit_value(stripped);
	g_quest_mark = exit_status;
	free(stripped);
}
