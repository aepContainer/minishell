/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:52:26 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:01:21 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*rtrn;
	size_t	multiplied;
	size_t	i;

	multiplied = count * size;
	rtrn = (char *) malloc(multiplied);
	if (!rtrn)
		return (0);
	i = 0;
	while (i < multiplied)
	{
		rtrn[i] = 0;
		i++;
	}
	return ((void *)rtrn);
}
