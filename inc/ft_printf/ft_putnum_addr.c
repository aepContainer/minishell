/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:11:20 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/22 19:27:30 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "ft_printf.h"

void	ft_putnum_addr(t_ul ul, int *printed)
{
	write(1, "0x", 2);
	(*printed) += 2;
	ft_putnum_hex_ul_arg(ul, printed);
}
