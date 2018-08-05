/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:05:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/05 20:06:21 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline void		open_files(int ac, char **av, t_vm *v, int i)
{
	while (++i < ac)
	{
		if ((v->player[v->player_amount].fd = open(av[i], O_RDONLY)) == -1)
			put_error(0, av[i], 0, 0);
		v->player[v->player_amount].filename = av[i];
		(++v->player_amount > MAX_PLAYERS) ? put_usage(3) : false;
	}
}

inline void		check_and_obtain_args(int ac, char **av, t_vm *v)
{
	int		i;

	(ac == 1) ? put_usage(1) : false;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-b"))
			v->args.is_binary = true;
		else if (ft_strequ(av[i], "-n"))
			v->args.is_ncurses = true;
		else if (ft_strequ(av[i], "--stealth"))
			v->args.is_stealth = true;
		else if (ft_strequ(av[i], "-d"))
		{
			(av[++i] == NULL) ? put_usage(2) : false;
			v->args.is_dump = true;
			v->args.dump_value = (unsigned int)ft_atoi(av[i]);
		}
		else
			break ;
	}
	open_files(ac, av, v, --i);
}
