/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:05:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/12 02:19:52 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		open_one_file(char **av, t_vm *v, int i)
{
	(av[i] == NULL) ? put_usage(4) : false;
	if ((v->player[v->player_amount].fd = open(av[i], O_RDONLY)) == -1)
		put_error(0, av[i], 0, 0);
	v->player[v->player_amount].filename = av[i];
	(++v->player_amount > MAX_PLAYERS) ? put_usage(3) : false;
}

static inline void		open_files(int ac, char **av, t_vm *v, int i)
{
	while (i < ac)
	{
		open_one_file(av, v, i++);
	}
	(v->player_amount <= 0) ? put_usage(4) : false;
}

inline void				check_and_obtain_args(int ac, char **av, t_vm *v)
{
	int		i;

	(ac == 1) ? put_usage(1) : false;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "--ncurses"))
			A.is_ncurses = true;
		else if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-dump")
		|| ft_strequ(av[i], "--dump"))
		{
			(av[++i] == NULL || !ft_isdigit(av[i][0])) ? put_usage(2) : false;
			A.is_dump = true;
			A.dump_value = (unsigned int)ft_atoi(av[i]);
		}
		else if (ft_strequ(av[i], "-v"))
		{
			(av[++i] == NULL || !ft_isdigit(av[i][0])) ? put_usage(6) : false;
			A.verbose_value = (unsigned int)ft_atoi(av[i]);
		}
		else if (ft_strequ(av[i], "--start_in"))
		{
			(av[++i] == NULL || !ft_isdigit(av[i][0])) ? put_usage(6) : false;
			A.vis_start_value = (unsigned int)ft_atoi(av[i]);
		}
		else if (ft_strequ(av[i], "--stealth"))
			A.is_stealth = true;
		else
			break ;
		// else if (ft_strequ(av[i], "-b"))
		// 	A.is_binary = true;
		// else if (ft_strequ(av[i], "--stealth"))
		// 	A.is_stealth = true;
		// else if (ft_strequ(av[i], "-n") || ft_strequ(av[i], "--number"))
		// {
		// 	(av[++i] == NULL) ? put_usage(5) : false;
		// 	A.is_dump = true;
		// 	A.dump_value = (unsigned int)ft_atoi(av[i]);
		// 	(A.dump_value <= 0) ? put_usage(5) : false;
		// 	open_one_file(av, v, ++i);
		// }
	}
	open_files(ac, av, v, i);
}
