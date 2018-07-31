/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/31 17:14:10 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			 put_usage(const int errnum)
{
	char			*errstr;

	(errnum == -1) ? errstr = "" : false;
	(errnum == 0) ? errstr = strerror(errnum) : false;
	(errnum == 1) ? errstr = "Too less arguments" : false;
	(errnum == 2) ? errstr = "There are no granted number for '-d' flag" : 0;
	(errnum == 3) ? errstr = "Too many champions" : false;
	(errnum == 4) ? errstr = "MAX_PALYERS useless value" : false;
	ft_printf("ERROR: %s\n\n%s\n", errstr,
	"Usage: ./corewar "
	"[-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>"
	"\t-d N\t\t: Dumps memory after N cycles then exits"
	"\t-b\t\t: Binary output mode for corewar.42.fr"
	"\t-n\t\t: Ncurses output mode"
	"\t--stealth\t: Hides the real contents of the memory");
	exit(1);
}

static void		open_files(int ac, const char **av, t_vm *v, int i)
{
	while (++i < ac)
	{
		if ((v->player[v->pa].fd = open(av[i], O_RDONLY)) == -1)
		{
			ft_printf("Can't read source file: %s", av[i]);
			put_usage(-1);
		}
		(++v->pa > MAX_PLAYERS) ? put_usage(3) : false;
	}
}

static void		check_and_obtain_args(int ac, const char **av, t_vm *v)
{
	int		i;

	(ac == 1) ? put_usage(1) : false;
	(MAX_PLAYERS <= 1) ? put_usage(4) : false;
	ft_bzero(v, sizeof(v)); // ???
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-b"))
			v->args.is_binary = 1;
		else if (ft_strequ(av[i], "-n"))
			v->args.is_ncurses = 1;
		else if (ft_strequ(av[i], "--stealth"))
			v->args.is_stealth = 1;
		else if (ft_strequ(av[i], "-d"))
		{
			(av[++i] == NULL) ? put_usage(2) : false;
			v->args.is_dump = 1;
			v->args.dump_value = (unsigned int)ft_atoi(av[i]);
		}
		else
			break ;
	}
	open_files(ac, av, v, i);
}

int				main(int ac, const char **av)
{
	t_vm		v;

	check_and_obtain_args(ac, av, &v);


	return (0);
}
