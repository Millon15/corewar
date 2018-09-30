/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:45:51 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 08:49:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <string.h>

static const char	g_usage[] = "Usage: ./corewar "
"-v N|(-d|-dump|--dump) N|--ncurses|-n N championN.cor"
" <champion1.cor> <...>\n"
"\t(-d|-dump|--dump) N\t: dumps memory after N cycles then exits\n"
"\t--ncurses\t\t: ncurses output mode\n"
"\t-n N championN.cor\t: sets the N of the next player\n"
"\t-v N\t\t\t: verbosity levels, can be added together to enable several\n"
"\t\t\t\t- 0 : Show only essentials\n"
"\t\t\t\t- 1 : Show lives\n"
"\t\t\t\t- 2 : Show cycles\n"
"\t\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n"
"\t\t\t\t- 8 : Show deaths\n"
"\t\t\t\t- 16 : Show PC movements (Except for jumps)\n";

bool				put_usage(const int errnum)
{
	const bool		is_invalid_error = errnum < 0 || errnum > 6;
	char			*errstr;
	const char		*errors[] = {"", "Too less arguments",
	"Wrong parameter passed to '-d' argument",
	"Too many champions", "At least one player needed for the game",
	"Wrong parameter passed to '-n' argument",
	"Wrong parameter passed to '-v' argument"};

	if (!is_invalid_error)
		errstr = (errnum == 0) ? strerror(errnum) : ((char **)errors)[errnum];
	else
		errstr = "";
	ft_dprintf(2, (is_invalid_error) ? "%.s%.s\n\n%s" : "%s%s\n\n%s",
	"Error: ", errstr, g_usage);
	exit(1);
}

bool				put_error(const int errnum, const char *errstr,
	const int i1, const int i2)
{
	const char		*errors[] = {"%sCan't read .cor file: %s\n",
	"%sFile %s has no magic number in its header\n",
	"%sFile %s has too large source code (%u bytes > %u bytes)\n"};

	ft_dprintf(2, errors[errnum], "Error: ", errstr, i1, i2);
	exit(2);
}
