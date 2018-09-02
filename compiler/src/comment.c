/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:41:43 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:41:44 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_valid_1line(char *line)
{
	int count;

	count = 0;
	while (*line != '"')
	{
		if (*line == ' ' || *line == '\t')
			;
		else
			count++;
		line++;
	}
	if (count != 8)
		exit(ft_printf("ERROR in .comment\n"));
}

static void		ft_valid_last_line(char *line, int type)
{
	while (*line != '"')
		line++;
	line++;
	if (type == 1)
	{
		while (*line != '"')
			line++;
		line++;
	}
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (*line == '#' || *line == ';')
			break ;
		else
			exit(ft_printf("ERROR in .comment\n"));
	}
}

static void		ft_comment1(t_champ **main_struct, int f)
{
	char *tmp;

	tmp = ft_memalloc(1);
	tmp = ft_strjoin_n(tmp, (*main_struct)->line + f, 0);
	get_next_line((*main_struct)->fd, &(*main_struct)->line);
	while (!ft_strstr_d((*main_struct)->line, "\""))
	{
		tmp = ft_strjoin_n(tmp, ft_strdup_d((*main_struct)->line, '#'), 1);
		if (!get_next_line((*main_struct)->fd, &(*main_struct)->line))
			exit(ft_printf("ERROR in .comment\n"));
	}
	ft_valid_last_line((*main_struct)->line, 0);
	tmp = ft_strjoin_n(tmp, ft_strdup_d((*main_struct)->line, '"'), 1);
	(*main_struct)->comment = tmp;
	if (ft_strlen((*main_struct)->comment) > 2048)
		exit(ft_printf("ERROR! .comment more then 2048 chars\n"));
}

void			ft_count_init(int *count)
{
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
}

void			ft_comment(t_champ **m_s)
{
	int i;

	i = 0;
	ft_count_init((*m_s)->count);
	ft_valid_1line((*m_s)->line);
	while ((*m_s)->line[i])
	{
		if ((*m_s)->line[i] == '"')
			(*m_s)->count[0]++;
		if ((*m_s)->count[0] == 1 && (*m_s)->count[1] == 0)
			(*m_s)->count[1] = i;
		if ((*m_s)->count[0] == 2 && (*m_s)->count[2] == 0)
			(*m_s)->count[2] = i;
		i++;
	}
	if ((*m_s)->count[0] == 2)
	{
		(*m_s)->comment = ft_strsub((*m_s)->line,
				(*m_s)->count[1] + 1, (*m_s)->count[2] - (*m_s)->count[1] - 1);
		ft_valid_last_line((*m_s)->line, 1);
	}
	else if ((*m_s)->count[0] == 1)
		ft_comment1(m_s, (*m_s)->count[1] + 1);
	else
		exit(ft_printf("ERROR in .comment\n"));
}
