/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:45:51 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 16:59:35 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <string.h>

bool		put_usage(const int errnum)
{
	const bool		is_invalid_error = errnum < 0 || errnum > 4;
	char			*errstr;
	char			*usage;
	const char		*errors[] = {"", "Too less arguments",
	"Wrong parameter passed to '-d' argument", "Too many champions",
	"At least one player needed for the game"};

	if (!is_invalid_error)
		errstr = (errnum == 0) ? strerror(errnum) : ((char **)errors)[errnum];
	else
		errstr = "";
	usage = "Usage: ./corewar "
	"[-d N -s N -v N | -b --stealth | -n --stealth] <champion1.cor> <...>\n"
	"\t-d N\t\t: Dumps memory after N cycles then exits\n"
	"\t-b\t\t: Binary output mode for corewar.42.fr\n"
	"\t-n\t\t: Ncurses output mode\n"
	"\t--stealth\t: Hides the real contents of the memory\n";
	ft_dprintf(2, (is_invalid_error) ? "%.s%.s\n\n%s" : "%s%s\n\n%s",
	"ERROR: ", errstr, usage);
	exit(1);
}

bool		put_error(const int errnum, const char *errstr,
	const int i1, const int i2)
{
	const char		*errors[] = {"%sCan't read .cor file: %s\n",
	"%sFile %s has no magic number in its header\n",
	"%sFile %s has too large source code (%u bytes > %u bytes)\n"};

	ft_dprintf(2, errors[errnum], "ERROR: ", errstr, i1, i2);
	exit(2);
}
