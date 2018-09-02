/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 15:40:36 by ndidenko          #+#    #+#             */
/*   Updated: 2017/12/09 15:40:37 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*current;
	size_t	i;

	i = 0;
	current = lst;
	if (current == NULL)
		return (0);
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
