/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <apyltsov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:05:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/24 17:21:14 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		open_one_file(char *av, int np, t_vm *v)
{
	// (av[i] == NULL) ? put_usage(4) : false;
	if ((v->player[np].fd = open(av, O_RDONLY)) == -1)
		put_error(0, av, 0, 0);
	v->player[np].filename = av;
	(++v->player_amount > MAX_PLAYERS) ? put_usage(3) : false;
}

static inline void		open_files(int ac, char **av, t_vm *v, int i)
{
	static int	max_np;
	int			np;
	int			j;

	j = i;
	while (av[i])
	{
		if (ft_strequ(av[i], "-n"))
		{
			if (!av[i + 1] || !av[i + 2] || (np = ft_atoi(av[i + 1])) > MAX_PLAYERS
			|| np < 1 || v->player[np - 1].fd != 0)
				put_usage(5);
			max_np = (np > max_np) ? np : max_np;
			open_one_file(av[i + 2], np - 1, v);
		}
		i++;
	}
	while(av[j])
	{
		if (!ft_strequ(av[j], "-n"))
		{
			np = 0;
			while (np < MAX_PLAYERS)
			{
				if (v->player[np].fd != 0)
					np++;
				else
					break;
			}
			open_one_file(av[j], np, v);
			j++;		
		}
		else
			j += 3;
	}
	if (max_np > v->player_amount)
		put_usage(5);	
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
		else if (ft_strequ(av[i], "--start-in"))
		{
			(av[++i] == NULL || !ft_isdigit(av[i][0])) ? put_usage(6) : false;
			A.vis_start_value = (unsigned int)ft_atoi(av[i]);
		}
		else if (ft_strequ(av[i], "--stealth"))
			A.is_stealth = true;
		else
			break ;
	}
	open_files(ac, av, v, i);
}
