/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:40:49 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 14:47:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int				meta_reader(const int fd, void *read_in, const int nbytes)
{
	int		ret;

	ret = read(fd, read_in, nbytes);
	if (ret < 0)
	{
		put_usage(0);
	}
	return (ret);
}

void			dump_printer(const void *to_print, const int nbytes)
{
	const unsigned char		*p = (const unsigned char *)to_print;
	int						i;

	i = -1;
	ft_printf("0x0000 : %0.2x ", p[++i]);
	while (++i < nbytes)
	{
		(!(i % 64)) ? ft_printf("\n%#.4x : %0.2x ", i, p[i]) :
		ft_printf("%0.2x ", p[i]);
	}
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

unsigned int	get_raw_num(const unsigned char *ar_ptr,
	const int bytes_to_read)
{
	unsigned int		res;
	int					b;

	res = 0;
	b = 0;
	while (b < bytes_to_read)
	{
		res <<= 8;
		res |= ar_ptr[b++];
	}
	return (res);
}
