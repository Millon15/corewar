/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/02 14:21:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <libftprintf.h>
# include <string.h>
# include <op.h>

typedef struct	s_args
{
	unsigned int	is_binary : 1;
	unsigned int	is_ncurses : 1;
	unsigned int	is_stealth : 1;
	unsigned int	is_dump : 1;
	unsigned int	dump_value;

}				t_args;

/*
** C
*/

typedef struct	s_player
{
	int				fd;
	t_op			header;

}				t_player;

/*
** C
*/

typedef struct	s_corewar
{
	unsigned int	pa;
	t_player		player[MAX_PLAYERS];
	t_args			args;
	char			arena[MEM_SIZE];
	// t_carriage		*head;
	// t_comms			p_tab[17];
	unsigned int	cursors;
	unsigned int	cycle;
	// unsigned int	tot_cycle;
	unsigned int	cycles_to_die;
	// unsigned int	lives;
	// unsigned int	check;
	// unsigned int	bonus;
	// unsigned int	winner;
	// unsigned int	last_alive;
	char		**files;

}				t_vm;

bool			 put_usage(const int errnum);

#endif
