/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:40:49 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:59:06 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int				meta_reader(const int fd, void *read_in, const int nbytes)
{
	int			ret;

	ret = read(fd, read_in, nbytes);
	if (ret < 0)
		put_usage(0);
	return (ret);
}

void			dump_printer(const void *to_print, const int nbytes)
{
	const unsigned char		*p = (const unsigned char *)to_print;
	int						i;

	i = -1;
	ft_printf("0x0000 : %0.2x ", p[++i]);
	while (++i < nbytes)
		(!(i % 64)) ? ft_printf("\n%#.4x : %0.2x ", i, p[i]) :
		ft_printf("%0.2x ", p[i]);
	ft_putchar('\n');
	exit(0);
}

unsigned int	read_raw_num(const int fd, const int chars_to_read)
{
	unsigned int		res;
	unsigned char		buf[chars_to_read];
	int					b;

	ft_bzero(&buf, chars_to_read);
	meta_reader(fd, buf, chars_to_read);
	res = 0;
	b = 0;
	while (b < chars_to_read)
	{
		res <<= 8;
		res |= buf[b++];
	}
	return (res);
}

int				get_raw_num(const unsigned char *arena,
	int bytes_to_read, const t_vm *v)
{
	const unsigned char		*end_of_arena = v->arena + MEM_SIZE;
	int						res;
	int						b;
	bool					sign;

	sign = 0;
	if (bytes_to_read > (int)sizeof(res))
		return (0);
	sign = (bool)(*arena & 0x80);
	res = 0;
	b = 0;
	while (b < bytes_to_read)
	{
		if (arena + b >= end_of_arena)
		{
			arena = v->arena;
			bytes_to_read -= b;
			b = 0;
		}
		res <<= 8;
		res |= !sign ? arena[b++] : arena[b++] ^ 0xFF;
	}
	sign ? res = ~(res) : 1;
	return (res);
}

int				obtain_argval(t_vm *v, t_car *self, int index, bool mod)
{
	int			value;
	int			addr;

	value = 0;
	if (self->args[index] == T_REG)
		value = self->reg[self->arg_val[index]];
	else if (self->args[index] == T_DIR)
		value = self->arg_val[index];
	else if (self->args[index] == T_IND)
	{
		addr = self->arg_val[index];
		value = get_raw_num(&v->arena[find_addr(PC_IND +
		(mod ? (addr % IDX_MOD) : addr))], REG_SIZE, v);
	}
	return (value);
}
