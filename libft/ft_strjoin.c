/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:30:32 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 15:59:29 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtrn;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	rtrn = malloc(len1 + len2 + 1);
	if (!rtrn)
		return (0);
	len1 = 0;
	while (s1[len1])
	{
		rtrn[len1] = s1[len1];
		len1++;
	}
	len2 = 0;
	while (s2[len2])
	{
		rtrn[len1 + len2] = s2[len2];
		len2++;
	}
	rtrn[len1 + len2] = 0;
	return (rtrn);
}
