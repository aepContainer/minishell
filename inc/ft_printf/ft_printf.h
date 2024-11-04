/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:06:23 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 19:24:11 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "stdarg.h"
# include "stdio.h"

typedef unsigned int	t_ui;
typedef unsigned long	t_ul;

int		ft_printf(const char *str, ...);
void	ft_print_perc(va_list arg_list, char perc, int *printed);
void	ft_putchar_arg(char c, int *printed);
void	ft_putnum_addr(t_ul ul, int *printed);
void	ft_putnum_hex_arg(t_ui i, char perc, int *printed);
void	ft_putnum_hex_ul_arg(t_ul ul, int *printed);
void	ft_putnum_sdec_arg(int i, int *printed);
void	ft_putnum_udec_arg(t_ui ui, int *printed);
void	ft_putstr_arg(char *str, int *printed);

#endif
