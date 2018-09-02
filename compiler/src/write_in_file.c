/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:42:48 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:42:50 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_write_bytes(int fd, int c, int bytes)
{
	int				j;
	unsigned char	mass[bytes];

	j = bytes;
	while (bytes)
	{
		bytes--;
		mass[bytes] = (unsigned char)c;
		c >>= 8;
	}
	while (bytes < j)
	{
		write(fd, &mass[bytes], 1);
		bytes++;
	}
}

static void		ft_write_name(t_champ *main_struct)
{
	int		i;
	int		bot_size;

	bot_size = ft_botsize(main_struct);
	i = 0;
	ft_write_bytes(main_struct->fd, COREWAR_EXEC_MAGIC, 4);
	while (main_struct->name[i])
	{
		ft_write_bytes(main_struct->fd, main_struct->name[i], 1);
		i++;
	}
	while (i < 132)
	{
		ft_write_bytes(main_struct->fd, 0, 1);
		i++;
	}
	ft_write_bytes(main_struct->fd, bot_size, 4);
}

static void		ft_write_comment(t_champ *main_struct)
{
	int i;

	i = 0;
	while (main_struct->comment[i])
	{
		ft_write_bytes(main_struct->fd, main_struct->comment[i], 1);
		i++;
	}
	i++;
	while (i < 2053)
	{
		ft_write_bytes(main_struct->fd, 0, 1);
		i++;
	}
}

static void		ft_write_cmd(t_champ *main_struct)
{
	t_arg		*arg;
	t_command	*command;

	command = main_struct->cmds;
	while (command)
	{
		if (!ft_strequ(command->name, "-1"))
		{
			arg = command->inst;
			ft_write_bytes(main_struct->fd, command->opcode, 1);
			if (command->codage)
				ft_write_bytes(main_struct->fd, command->codage, 1);
			while (arg)
			{
				ft_write_bytes(main_struct->fd, arg->value, arg->size);
				arg = arg->next;
			}
		}
		command = command->next;
	}
}

void			ft_write_in_file(char *argv, t_champ *main_struct)
{
	char	*file_name;
	int		argv_len;

	argv_len = ft_strlen(argv);
	if (!main_struct->name || !main_struct->comment)
		exit(ft_printf("ERROR! file must contain .name and .comment\n"));
	if (argv[argv_len - 2] != '.' || argv[argv_len - 1] != 's')
		exit(ft_printf("ERROR! is not .s file!\n"));
	file_name = ft_strsub(argv, 0, argv_len - 2);
	file_name = ft_strjoin_n(file_name, ".cor", 0);
	file_name[ft_strlen(file_name) - 1] = '\0';
	main_struct->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	ft_write_name(main_struct);
	ft_write_comment(main_struct);
	ft_write_cmd(main_struct);
	ft_printf("Writing output program to %s\n", file_name);
	free(file_name);
	close(main_struct->fd);
}
