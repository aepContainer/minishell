/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_hex_ul_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:22:10 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 19:25:31 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"

void	ft_putnum_hex_ul_arg(t_ul ul, int *printed)
{
	if (ul > 15)
	{
		ft_putnum_hex_ul_arg(ul / 16, printed);
		ft_putnum_hex_ul_arg(ul % 16, printed);
	}
	else
	{
		write(1, &"0123456789abcdef"[ul], 1);
		(*printed)++;
	}
}
