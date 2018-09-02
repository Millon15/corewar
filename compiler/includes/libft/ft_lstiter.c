/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:33:11 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 16:08:51 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list*elem))
{
	t_list	*lst2;

	lst2 = lst;
	if (lst == 0 || f == 0)
		return ;
	else
	{
		while (lst2 != 0)
		{
			f(lst2);
			lst2 = lst2->next;
		}
	}
}
