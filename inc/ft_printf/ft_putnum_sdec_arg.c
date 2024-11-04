/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_sdec_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:32:16 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 18:23:24 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "ft_printf.h"

void	ft_putnum_sdec_arg(int i, int *printed)
{
	char	c;

	if (i == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*printed) += 11;
		return ;
	}
	else if (i < 0)
	{
		write(1, "-", 1);
		(*printed)++;
		ft_putnum_sdec_arg(-i, printed);
		return ;
	}
	else if (i > 9)
	{
		ft_putnum_sdec_arg(i / 10, printed);
		ft_putnum_sdec_arg(i % 10, printed);
		return ;
	}
	c = i + 48;
	write(1, &c, 1);
	(*printed)++;
}
