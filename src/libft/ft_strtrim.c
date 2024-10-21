/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:31:49 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:08 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	fr;
	size_t	end;
	size_t	len1;

	if (!s1 || !set)
		return (0);
	fr = 0;
	while (s1[fr] && ft_strchr(set, s1[fr]))
		fr++;
	len1 = ft_strlen(s1);
	if (fr == len1)
		return (ft_strdup(""));
	end = len1 - 1;
	while (end > fr && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, fr, end - fr + 1));
}
