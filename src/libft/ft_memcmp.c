/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:46:30 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:57 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_uc	*cpys1;
	t_uc	*cpys2;
	size_t	i;

	cpys1 = (t_uc *) s1;
	cpys2 = (t_uc *) s2;
	i = 0;
	while (i < n)
	{
		if (cpys1[i] != cpys2[i])
			return (cpys1[i] - cpys2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (cpys1[i] - cpys2[i]);
}
