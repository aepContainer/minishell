/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_hex_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:31:09 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 19:24:52 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "ft_printf.h"

void	ft_putnum_hex_arg(t_ui ui, char perc, int *printed)
{
	if (ui > 15)
	{
		ft_putnum_hex_arg(ui / 16, perc, printed);
		ft_putnum_hex_arg(ui % 16, perc, printed);
	}
	else
	{
		if (perc == 'x')
			write(1, &"0123456789abcdef"[ui], 1);
		else
			write(1, &"0123456789ABCDEF"[ui], 1);
		(*printed)++;
	}
}
