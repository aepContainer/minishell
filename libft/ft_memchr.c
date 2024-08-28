/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:41:17 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/21 17:40:46 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	t_uc	*cpys;
	size_t	i;

	cpys = (t_uc *) s;
	i = 0;
	while (i < len)
	{
		if (cpys[i] == (t_uc) c)
			return ((void *)(cpys + i));
		i++;
	}
	return (0);
}
