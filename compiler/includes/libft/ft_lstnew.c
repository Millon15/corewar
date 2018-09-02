/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:13:29 by ndidenko          #+#    #+#             */
/*   Updated: 2017/12/08 14:56:41 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlist;
	void	*contentnew;
	size_t	sizenew;

	if ((newlist = (t_list*)malloc(sizeof(t_list))) == 0)
		return (0);
	if (content == 0)
	{
		newlist->content = 0;
		newlist->content_size = 0;
	}
	else
	{
		contentnew = ft_memalloc(content_size);
		sizenew = content_size;
		ft_memcpy(contentnew, content, sizenew);
		newlist->content = contentnew;
		newlist->content_size = sizenew;
	}
	newlist->next = 0;
	return (newlist);
}
