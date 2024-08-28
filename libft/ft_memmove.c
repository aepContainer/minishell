/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:04:35 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:53 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	short	chngi;

	if (!dst && !src)
		return (dst);
	chngi = 1;
	if (dst <= src)
		i = 0;
	else
	{
		chngi = -1;
		i = len - 1;
	}
	while (i < len && i >= 0)
	{
		((char *) dst)[i] = ((char *) src)[i];
		if (i == 0 && chngi == -1)
			break ;
		i = i + chngi;
	}
	dst = (void *) dst;
	return (dst);
}
