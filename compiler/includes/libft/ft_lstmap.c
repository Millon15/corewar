/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:37:58 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/29 19:38:12 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*node;
	t_list	*xyz;

	if (lst == 0 || f == 0)
		return (NULL);
	node = f(lst);
	start = node;
	lst = lst->next;
	while (lst)
	{
		xyz = f(lst);
		node->next = xyz;
		node = xyz;
		lst = lst->next;
	}
	node->next = NULL;
	return (start);
}
