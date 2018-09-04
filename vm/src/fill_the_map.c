/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:56:29 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/04 18:40:32 by vbrazas          ###   ########.fr       */
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
		P(i).name = UINT_MAX - i;
		P(i).lives_in_cp = 0;
		P(i).points = 0;
		P(i).magic = read_raw_num(P(i).fd, sizeof(int));
		if (P(i).magic != COREWAR_EXEC_MAGIC)
			put_error(1, P(i).filename, 0, 0);
		meta_reader(P(i).fd, P(i).prog_name, PROG_NAME_LENGTH);
		lseek(P(i).fd, sizeof(int), SEEK_CUR);
		P(i).prog_size = read_raw_num(P(i).fd, sizeof(int));
		meta_reader(P(i).fd, P(i).comment, COMMENT_LENGTH);
		lseek(P(i).fd, sizeof(int), SEEK_CUR);
		ret = meta_reader(P(i).fd, P(i).source_code, MEM_SIZE);
		(ret > ((int)P(i).prog_size)) ? put_error(2,
		P(i).filename, P(i).prog_size, CHAMP_MAX_SIZE) : 0;
		P(i).is_alive = true;
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
		init_car(arena, P(i).name, v);
		ft_memcpy(arena, P(i).source_code, P(i).prog_size);
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
		i + 1, P(i).prog_size,
		P(i).prog_name, P(i).comment);
}
