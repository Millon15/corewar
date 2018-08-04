/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:56:29 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/04 20:13:25 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		fill_player_struct(t_vm *v)
{
	int			ret;
	int			i;

	i = -1;
	while (++i < v->player_amount)
	{
		v->player[i].magic = read_raw_num(v->player[i].fd, sizeof(int));
		if (v->player[i].magic != COREWAR_EXEC_MAGIC &&
		ft_dprintf(2, "ERROR: File %s has no magic number in its header\n",
		v->player[i].filename))
			exit(2);
		meta_reader(v->player[i].fd, v->player[i].prog_name, PROG_NAME_LENGTH);
		lseek(v->player[i].fd, sizeof(int), SEEK_CUR);
		v->player[i].prog_size = read_raw_num(v->player[i].fd, sizeof(int));
		meta_reader(v->player[i].fd, v->player[i].comment, COMMENT_LENGTH);
		lseek(v->player[i].fd, sizeof(int), SEEK_CUR);
		ret = meta_reader(v->player[i].fd, v->player[i].source_code, MEM_SIZE);
		if (ret > ((int)v->player[i].prog_size) && ft_dprintf(2,
		"ERROR: File %s has too large source code (%u bytes > %u bytes)\n",
		v->player[i].filename, v->player[i].prog_size, CHAMP_MAX_SIZE))
			exit(2);
	}
}

static inline void		fill_arena(t_vm *v)
{
	const int		increase_on = MEM_SIZE / v->player_amount;
	unsigned char	*arena;
	int				i;

	i = -1;
	arena = v->arena;
	while (++i < v->player_amount)
	{
		ft_memcpy(arena, v->player[i].source_code, v->player[i].prog_size);
		arena += increase_on * sizeof(char);
	}
}

void				fill_the_map(t_vm *v)
{
	fill_player_struct(v);
	fill_arena(v);
}
