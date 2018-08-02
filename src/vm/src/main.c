/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/02 14:30:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

bool					put_usage(const int errnum)
{
	const bool		is_invalid_error = (errnum < 0 || errnum > 4);
	char			*errstr;
	const char		*errors[] = {"", "Too less arguments",
	"There are no granted number for '-d' flag",
	"Too many champions",
	"MAX_PALYERS useless value"};

	if (is_invalid_error)
		errstr = "";
	else
		errstr = (errnum == 0) ? strerror(errnum) : ((char **)errors)[errnum];
	ft_dprintf(2, "%s%s\n\n%s", (is_invalid_error) ? "" : "ERROR: ",
	errstr, "Usage: ./corewar "
	"[-d N -s N -v N | -b --stealth | -n --stealth] <champion1.cor> <...>\n"
	"\t-d N\t\t: Dumps memory after N cycles then exits\n"
	"\t-b\t\t: Binary output mode for corewar.42.fr\n"
	"\t-n\t\t: Ncurses output mode\n"
	"\t--stealth\t: Hides the real contents of the memory\n");
	exit(1);
}

static inline void		open_files(int ac, const char **av, t_vm *v, int i)
{
	while (++i < ac)
	{
		if ((v->player[v->pa].fd = open(av[i], O_RDONLY)) == -1)
			ft_dprintf(2, "Can't read source file: %s", av[i]) && put_usage(-1);
		(++v->pa > MAX_PLAYERS) ? put_usage(3) : false;
	}
}

static inline void		check_and_obtain_args(int ac, const char **av, t_vm *v)
{
	int		i;

	(ac == 1) ? put_usage(1) : false;
	(MAX_PLAYERS <= 1) ? put_usage(4) : false;
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
	open_files(ac, av, v, --i);
}

int						main(int ac, const char **av)
{
	t_vm		v;

	ft_bzero(&v, sizeof(v));
	check_and_obtain_args(ac, av, &v);
	return (0);
}
