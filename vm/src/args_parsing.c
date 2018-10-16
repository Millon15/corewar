/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:05:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/16 20:05:46 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		open_one_file(char *av, int np, t_vm *v)
{
	if ((v->player[np].fd = open(av, O_RDONLY)) == -1)
		put_error(0, av, 0, 0);
	v->player[np].filename = av;
	(++v->player_amount > MAX_PLAYERS) ? put_usage(3) : false;
}

static inline void		help_handle_n(char **av, int j, t_vm *v)
{
	int					np;

	while (av[j])
	{
		if (!ft_strequ(av[j], "-n"))
		{
			np = 0;
			while (np < MAX_PLAYERS)
				if (v->player[np].fd != 0)
					np++;
				else
					break ;
			open_one_file(av[j], np, v);
			j++;
		}
		else
			j += 3;
	}
}

static inline void		handle_n(int ac, char **av, t_vm *v, int i)
{
	static int	max_np;
	int			np;
	int			j;

	j = i;
	while (av[i])
	{
		if (ft_strequ(av[i], "-n"))
		{
			if (!av[i + 1] || !av[i + 2]
			|| (np = ft_atoi(av[i + 1])) > MAX_PLAYERS
			|| np < 1 || P(np - 1).fd != 0)
				put_usage(5);
			max_np = (np > max_np) ? np : max_np;
			open_one_file(av[i + 2], np - 1, v);
		}
		i++;
	}
	help_handle_n(av, j, v);
	if (max_np > v->player_amount)
		put_usage(5);
}

static inline int		help_check_and_obtain_args(char **av, int i, t_vm *v)
{
	if (ft_strequ(av[i], "--ncurses"))
		A.is_ncurses = true;
	else if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-dump"))
		(A.is_dump = true)
		&& (A.dump_value = (unsigned int)ft_atoi(av[++i]));
	else if (ft_strequ(av[i], "-v"))
		(av[++i] == NULL || !ft_isdigit(av[i][0])) ?
		put_usage(6) : (A.verbose_value = (unsigned int)ft_atoi(av[i]));
	else if (ft_strequ(av[i], "--start-in"))
		(av[++i] == NULL || !ft_isdigit(av[i][0]) || !A.is_ncurses) ?
		put_usage(7) : (A.vis_start_value = (unsigned int)ft_atoi(av[i]));
	else if (ft_strequ(av[i], "--stealth"))
		(!A.is_ncurses) ? put_usage(8) : (A.is_stealth = true);
	else if (ft_strequ(av[i], "--venom"))
		(M.is_music = true)
		&& (M.is_venom = true);
	else if (ft_strequ(av[i], "--skibidi"))
		(M.is_music = true)
		&& (M.is_skibidi = true);
	else if (ft_strequ(av[i], "--no-stat"))
		(A.is_nostat = true);
	else
		return (-1);
	return (i);
}

inline void				check_and_obtain_args(int ac, char **av, t_vm *v)
{
	int		i;
	int		j;

	i = 0;
	while (++i < ac)
	{
		if ((j = help_check_and_obtain_args(av, i, v)) == -1)
			break ;
		else
			i = j;
	}
	(i >= ac) ? put_usage(4) : false;
	handle_n(ac, av, v, i);
}
