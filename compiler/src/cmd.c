/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:39:49 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:39:50 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_valid_command_line(char *line, int command)
{
	int			len;
	char		*msg;

	msg = line;
	if (ft_detect_label(line) != 0)
	{
		while (*line != ':')
			line++;
		line++;
	}
	if (*line == '\0' || *line == '\n')
		return ;
	len = ft_strlen(g_operations[command].name);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strnequ(line, g_operations[command].name, len) != 1)
		exit(ft_printf("ERROR in line: |%s|\n", msg));
}

t_command		*ft_parse_cmd(char *line)
{
	t_command	*cmd_tmp;
	char		*ptr;
	int			command;

	command = ft_detect_command_i(line);
	ft_valid_command_line(line, command);
	cmd_tmp = (t_command*)malloc(sizeof(t_command));
	ft_memset(cmd_tmp, 0, sizeof(t_command));
	cmd_tmp->next = NULL;
	if (command != -1)
	{
		ptr = ft_detect_command(line);
		cmd_tmp->name = ft_strsub(ft_detect_command(line), 0,
						ft_strlen(g_operations[command].name));
		cmd_tmp->inst = 0;
		cmd_tmp->codage = g_operations[command].codage;
		cmd_tmp->opcode = g_operations[command].opcode;
		if (ft_strlen(cmd_tmp->name) < 1)
			cmd_tmp->name = ft_strdup("-1");
	}
	else
		cmd_tmp->name = ft_strdup("-1");
	return (cmd_tmp);
}

void			cmd_in_end(t_command **a, t_command *b)
{
	t_command	*start;

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

void			ft_valid_next_line(t_champ **main_struct)
{
	while (ft_emptyline((*main_struct)->line))
	{
		free((*main_struct)->line);
		get_next_line((*main_struct)->fd, &(*main_struct)->line);
	}
	if (ft_detect_command((*main_struct)->line) == 0
					&& ft_detect_label((*main_struct)->line) == 0)
		exit(ft_printf("ERROR! command not found after label\n"));
}

void			ft_cmd(t_champ **main_struct)
{
	t_command	*cmd_s;
	char		*arg_s;
	t_label		*label_s;

	cmd_s = NULL;
	arg_s = NULL;
	label_s = NULL;
	while (ft_detect_label((*main_struct)->line))
	{
		ft_parse_label((*main_struct)->line, &label_s);
		if (ft_detect_command_i((*main_struct)->line) >= 0)
			break ;
		free((*main_struct)->line);
		if (!get_next_line((*main_struct)->fd, &(*main_struct)->line))
			break ;
		ft_valid_next_line(main_struct);
	}
	cmd_s = ft_parse_cmd((*main_struct)->line);
	cmd_s->labels = label_s;
	if (ft_detect_command((*main_struct)->line) != 0)
		ft_parse_arg((*main_struct)->line, &cmd_s);
	cmd_in_end(&(*main_struct)->cmds, cmd_s);
}
