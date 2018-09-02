/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:39:28 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:39:29 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			arg_in_end(t_arg **a, t_arg *b)
{
	t_arg	*start;

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

unsigned int	atoi_arg(const char *str)
{
	unsigned	int	res;
	int				n;

	res = 0;
	n = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		n = n - 2;
	if (*str == '+' || *str == '-')
		str++;
	if (*str < 48 && *str > 57)
		exit(ft_printf("ERROR! not valid value!\n"));
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	while (*str++)
		if (*str != ' ' || *str != '\t')
			exit(ft_printf("ERROR! not valid value!\n"));
	return (res * n);
}

static void		ft_arg_label(char *line, int command, int i, t_arg **arg)
{
	char	*start;

	if (i + 1 == g_operations[command].count_args
			&& ft_strchr(line, COMMENT_CHAR))
		(*arg)->name_label =
			ft_strdup_d(line, COMMENT_CHAR);
	else
		(*arg)->name_label = ft_strdup(line + 1);
	start = (*arg)->name_label;
	while (*start)
	{
		if (!ft_strchr(LABEL_CHARS, *start))
			exit(ft_printf("ERROR! '%c' is forbidden in label-name\n", *start));
		start++;
	}
	(*arg)->value = -1;
}

void			ft_parse_ind(char *line, int command, int i, t_command **cmd_s)
{
	t_arg	*a;
	int		j;

	j = 0;
	a = (t_arg*)malloc(sizeof(t_arg));
	if (line[0] == LABEL_CHAR)
		ft_arg_label(line, command, i, &a);
	else
	{
		if (line[0] == '-')
			j++;
		while (line[j] && ft_isdigit(line[j]))
			j++;
		if (i + 1 != g_operations[command].count_args
			&& line[j])
			exit(ft_printf("ERROR in arg T_IND\n"));
		a->name_label = 0;
		a->value = atoi_arg(line);
	}
	a->size = IND_SIZE;
	a->binary = 3;
	arg_in_end(&(*cmd_s)->inst, a);
}
