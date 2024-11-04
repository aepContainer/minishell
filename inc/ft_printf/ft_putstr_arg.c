/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:29:41 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/21 18:17:04 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "ft_printf.h"

void	ft_putstr_arg(char *str, int *printed)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*printed += 6;
		return ;
	}
	while (*str)
	{
		write(1, str, 1);
		(*printed)++;
		str++;
	}
}
