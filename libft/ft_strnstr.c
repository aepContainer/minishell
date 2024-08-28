/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:09:04 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:13 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	if (!*needle)
		return ((char *) haystack);
	i = 0;
	nlen = ft_strlen(needle);
	while (haystack[i] && nlen <= len)
	{
		j = 0;
		if (haystack[i] == needle[j] && !ft_strncmp(haystack + i, needle, nlen))
			return ((char *)(haystack + i));
		len--;
		i++;
	}
	return (0);
}
