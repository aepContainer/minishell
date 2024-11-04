/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_perc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:26:58 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 19:28:41 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdarg.h"
#include "ft_printf.h"

void	ft_print_perc(va_list arg_list, char perc, int *printed)
{
	if (arg_list && perc == '%')
		ft_putchar_arg('%', printed);
	else if (arg_list && perc == 'c')
		ft_putchar_arg(va_arg(arg_list, int), printed);
	else if (arg_list && perc == 's')
		ft_putstr_arg(va_arg(arg_list, char *), printed);
	else if (arg_list && perc == 'p')
	{
		ft_putnum_addr(va_arg(arg_list, t_ul), printed);
	}
	else if (arg_list && (perc == 'x' || perc == 'X'))
		ft_putnum_hex_arg(va_arg(arg_list, t_ui), perc, printed);
	else if (arg_list && (perc == 'd' || perc == 'i'))
		ft_putnum_sdec_arg(va_arg(arg_list, int), printed);
	else if (arg_list && perc == 'u')
		ft_putnum_udec_arg(va_arg(arg_list, t_ui), printed);
}
