/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:53:48 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 20:26:44 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdarg.h"
#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg_list;
	size_t	i;
	int		printed;

	if (!str)
		return (0);
	va_start(arg_list, str);
	printed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			printed++;
		}
		else
		{
			ft_print_perc(arg_list, str[i + 1], &printed);
			i++;
		}
		i++;
	}
	va_end(arg_list);
	return (printed);
}
