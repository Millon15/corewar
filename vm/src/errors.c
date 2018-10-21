/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:45:51 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 06:36:07 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <string.h>

static const char		g_usage[] = "Usage: ./corewar "
"[-v N] [(-d|-dump) N] [--ncurses [--stealth] [--start-in N] "
"[(--venom|--skibidi)]] [-n N champion.cor] <champion1.cor> <...>\n"
"\t(-d|-dump) N\t\t: dumps memory after N cycles then exits\n"
"\t--ncurses\t\t: ncurses output mode\n"
"\t\t\t\t--start-in N\t: waits N cycles, then starts the ncurses mode\n"
"\t\t\t\t--stealth\t: hides the real contents of the memory in ncurses mode\n"
"\t\t\t\t--no-stat\t: turn off stat(3rd) window in ncurses mode\n"
"\t\t\t\t--(venom|skibidi|bigshaq) : "
"playing last chosen sounds in ncurses mode\n"
"\t-n N champion.cor\t: sets the N of the next player\n"
"\t-v N\t\t\t: verbosity levels, can be added together to enable several\n"
"\t\t\t\t- 0\t: Show only essentials\n"
"\t\t\t\t- 1\t: Show lives\n"
"\t\t\t\t- 2\t: Show cycles\n"
"\t\t\t\t- 4\t: Show operations (Params are NOT litteral ...)\n"
"\t\t\t\t- 8\t: Show deaths\n";

static const char		*g_errors[] = {"", "Too less arguments",
	"Wrong parameter passed to '-d' argument",
	"Too many champions", "At least one player needed for the game",
	"Wrong parameter passed to '-n' argument",
	"Wrong parameter passed to '-v' argument",
	"'--start-in' can't be set-up without '--ncurses' argument",
	"'--stealth' can't be set-up without '--ncurses' argument",
	"'--venom' can't be set-up without '--ncurses' argument",
	"'--skibidi' can't be set-up without '--ncurses' argument",
	"'--bigshaq' can't be set-up without '--ncurses' argument",
	"'--no-stat' can't be set-up without '--ncurses' argument"
};

bool					put_usage(const int errnum)
{
	const bool		is_invalid_error = errnum < 0 || errnum > 6;
	char			*errstr;

	if (!is_invalid_error)
		errstr = (errnum == 0) ? strerror(errnum) : ((char **)g_errors)[errnum];
	else
		errstr = "";
	ft_dprintf(2, (is_invalid_error) ? "%.s%.s\n\n%s" : "%s%s\n\n%s",
	"Error: ", errstr, g_usage);
	exit(1);
}

bool					put_error(const int errnum, const char *errstr
	, const int i1, const int i2)
{
	const char		*errors[] = {"%sCan't read .cor file: %s\n",
	"%sFile %s has no magic number in its header\n",
	"%sFile %s has too large source code (%u bytes > %u bytes)\n"};

	ft_dprintf(2, errors[errnum], "Error: ", errstr, i1, i2);
	exit(2);
}
