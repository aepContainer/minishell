/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:35:43 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/19 17:28:46 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_of_digit(int n)
{
	size_t	counted;

	counted = 0;
	if (n < 0)
	{
		counted++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		counted++;
	}
	return (counted + 1);
}

char	*ft_itoa(int n)
{
	char	*rtrn;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_num_of_digit(n);
	rtrn = (char *) malloc(len + 1);
	if (!rtrn)
		return (0);
	rtrn[len] = 0;
	if (n < 0)
	{
		n *= -1;
		rtrn[0] = '-';
	}
	while (n >= 0)
	{
		rtrn[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
		if (n == 0)
			break ;
	}
	return (rtrn);
}
