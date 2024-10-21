/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:35:22 by apalaz            #+#    #+#             */
/*   Updated: 2023/12/10 20:38:27 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtrn;
	t_list	*changed;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	rtrn = NULL;
	while (lst)
	{
		temp = f(lst->content);
		if (!temp)
			return (ft_lstclear(&rtrn, del), NULL);
		changed = ft_lstnew(temp);
		if (!changed)
			return (ft_lstclear(&rtrn, del), del(temp), NULL);
		ft_lstadd_back(&rtrn, changed);
		lst = lst->next;
	}
	return (rtrn);
}
