/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:10:40 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 18:10:43 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*ft_create_label(void)
{
	t_label *newlabel;

	newlabel = (t_label*)malloc(sizeof(t_label));
	newlabel->name = NULL;
	newlabel->next = NULL;
	return (newlabel);
}

void		label_in_end(t_label **a, t_label *b)
{
	t_label	*start;

	start = *a;
	if (*a)
	{
		while (start->next)
			start = start->next;
		start->next = b;
		b->next = 0;
	}
	else
	{
		b->next = *a;
		*a = b;
	}
}

void		ft_parse_label(char *line, t_label **label_s)
{
	char	*tmp;
	t_label	*labeltmp;

	tmp = line;
	if (ft_detect_command(line) == 0)
	{
		while (*tmp != ':')
			tmp++;
		tmp++;
		if (ft_emptyline(tmp) == 0)
			exit(ft_printf("ERROR in ENDLINE: |%s|\n", line));
	}
	labeltmp = ft_create_label();
	while (*line == ' ' || *line == '\t')
		line++;
	labeltmp->name = ft_strsub(line, 0, ft_detect_label(line));
	labeltmp->next = NULL;
	label_in_end(&(*label_s), labeltmp);
}
