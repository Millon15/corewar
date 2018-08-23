/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:56:29 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/23 18:35:54 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		fill_players(t_vm *v)
{
	int					ret;
	int					i;

	i = -1;
	while (++i < v->player_amount)
	{
		v->player[i].name = UINT_MAX - i;
		v->player[i].lives_in_cp = 0;
		v->player[i].points = 0;
		v->player[i].magic = read_raw_num(v->player[i].fd, sizeof(int));
		if (v->player[i].magic != COREWAR_EXEC_MAGIC)
			put_error(1, v->player[i].filename, 0, 0);
		meta_reader(v->player[i].fd, v->player[i].prog_name, PROG_NAME_LENGTH);
		lseek(v->player[i].fd, sizeof(int), SEEK_CUR);
		v->player[i].prog_size = read_raw_num(v->player[i].fd, sizeof(int));
		meta_reader(v->player[i].fd, v->player[i].comment, COMMENT_LENGTH);
		lseek(v->player[i].fd, sizeof(int), SEEK_CUR);
		ret = meta_reader(v->player[i].fd, v->player[i].source_code, MEM_SIZE);
		(ret > ((int)v->player[i].prog_size)) ? put_error(2,
		v->player[i].filename, v->player[i].prog_size, CHAMP_MAX_SIZE) : 0;
		v->player[i].is_alive = true;
	}
}

void		fill_arena(t_vm *v)
{
	const int		increase_on = MEM_SIZE / v->player_amount;
	unsigned char	*arena;
	int				i;

	i = -1;
	arena = v->arena;
	while (++i < v->player_amount)
	{
		init_car(arena, v->player[i].name, v);
		ft_memcpy(arena, v->player[i].source_code, v->player[i].prog_size);
		arena += increase_on * sizeof(char);
	}
}

void		print_arena(t_vm *v)
{
	int				i;

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < v->player_amount)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i + 1, v->player[i].prog_size,
		v->player[i].prog_name, v->player[i].comment);
	if (v->args.is_dump)
		meta_printer(v->arena, MEM_SIZE);
	exit(0);
}
