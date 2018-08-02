/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:56:29 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/02 22:27:26 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static int			meta_reader(int fd, char read_in[], int nbytes)
{
	int		ret;

	ret = read(fd, read_in, nbytes);
	if (ret < 0)
	{
		put_usage(0);
	}
	return (ret);
}

static inline void	fill_player_struct(t_vm *v)
{
	ssize_t		ret;
	int			i;

	i = -1;
	while (++i < v->player_amount)
	{
		ret =
		meta_reader(v->player[i].fd, v->player[i].prog_name, PROG_NAME_LENGTH);
		(ret < 0) ? put_usage(0) : false;
		ret =
		meta_reader(v->player[i].fd, v->player[i].comment, COMMENT_LENGTH);
		(ret < 0) ? put_usage(0) : false;
		ret =
		meta_reader(v->player[i].fd, v->player[i].source_code, MEM_SIZE);
		if (ret > CHAMP_MAX_SIZE)
		{
			ft_dprintf(2,
			"ERROR: File %s has too large source code (%u bytes > %u bytes)\n",
			v->player[i].filename, ret, CHAMP_MAX_SIZE);
			exit(2);
		}
		v->player[i].prog_size = ret;
	}
}

static inline void	fill_arena(t_vm *v)
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
