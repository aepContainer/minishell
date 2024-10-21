/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:32:28 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/17 14:37:33 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *str, char c)
{
	size_t	counted;
	size_t	i;
	short	state;

	counted = 0;
	i = 0;
	while (str[i])
	{
		state = 0;
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i])
		{
			state = 1;
			i++;
		}
		if (state == 1)
			counted++;
	}
	return (counted);
}

char	**ft_split(char const *s2, char c)
{
	char	**rtrn;
	size_t	rtrni;
	size_t	index;
	size_t	ios;

	if (!s2)
		return (0);
	rtrn = (char **) malloc(sizeof(char *) * (ft_count_word(s2, c) + 1));
	if (!rtrn)
		return (0);
	index = 0;
	rtrni = 0;
	while (s2[index])
	{
		while (s2[index] == c)
			index++;
		ios = index;
		while (s2[index] != c && s2[index] != '\0')
			index++;
		if (ios < index)
			rtrn[rtrni++] = ft_substr(s2, ios, index - ios);
	}
	rtrn[rtrni] = 0;
	return (rtrn);
}
