/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:40:21 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:40:22 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_emptyline(char *line)
{
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			;
		else if (*line == '#' || *line == ';')
			return (1);
		else
			return (0);
		line++;
	}
	return (1);
}

void		ft_init(t_champ **m_s, int argc, char **argv)
{
	if (argc == 1)
		exit(ft_printf("Please add argument\n"));
	(*m_s) = (t_champ*)malloc(sizeof(t_champ));
	(*m_s)->name = 0;
	(*m_s)->comment = 0;
	(*m_s)->line = 0;
	(*m_s)->cmds = 0;
	(*m_s)->fd = open(argv[1], O_RDONLY);
	if ((*m_s)->fd == -1)
		exit(ft_printf("ERROR! fd is -1\n"));
}

int			main(int argc, char **argv)
{
	t_champ	*m_s;

	ft_init(&m_s, argc, argv);
	while (get_next_line(m_s->fd, &m_s->line))
	{
		if (ft_strlen(m_s->line) < 1 || ft_emptyline(m_s->line))
		{
			free(m_s->line);
			continue;
		}
		else if (ft_strstr_d(m_s->line, ".name") && m_s->name == 0)
			ft_name(&m_s);
		else if (ft_strstr_d(m_s->line, ".comment") && m_s->comment == 0)
			ft_comment(&m_s);
		else if (ft_detect_command(m_s->line) != 0
			|| ft_detect_label(m_s->line) != 0)
			ft_cmd(&m_s);
		else
			exit(ft_printf("ERROR! not valid line: |%s|\n", m_s->line));
		free(m_s->line);
	}
	ft_set_value(&m_s);
	close(m_s->fd);
	ft_write_in_file(argv[1], m_s);
	return (0);
}
