/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:54:10 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:55 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cpydst;
	char	*cpysrc;
	size_t	i;

	if (!dst && !src)
		return (dst);
	cpydst = (char *) dst;
	cpysrc = (char *) src;
	i = 0;
	while (i < n)
	{
		cpydst[i] = cpysrc[i];
		i++;
	}
	dst = (void *) cpydst;
	return (dst);
}
