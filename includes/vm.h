/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/07/26 19:47:46 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include <libftprintf.h>
#include <op.h>

typedef struct		s_corewar
{
	// t_player	player[MAX_PLAYERS + 1];
	// t_cursor	*head;
	// t_arena		a[MEM_SIZE];
	int			cursors;
	// int			dump;
	// int			dump_value;
	// int			cycle;
	// int			tot_cycle;
	// int			lives;
	// int			check;
	// int			bonus;
	// int			winner;
	// int			last_alive;
	// int			cycles_to_die;
	// char		arena[MEM_SIZE];
	// int			player_amount;
	// char		**files;
	// t_op		p_tab[17];

}					t_core;

int				 put_usage(const int errnum);

#endif
