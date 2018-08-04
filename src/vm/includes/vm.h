/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/04 20:11:06 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <libftprintf.h>
# include <string.h>
# include <op.h>

/*
** Structure of passed args
*/

typedef struct	s_args
{
	unsigned int	is_binary : 1;
	unsigned int	is_ncurses : 1;
	unsigned int	is_stealth : 1;
	unsigned int	is_dump : 1;
	unsigned int	dump_value;

}				t_args;

/*
** Structure of the single player
*/

typedef struct	s_player
{
	int				fd;
	char			*filename;
	unsigned int	magic;
	unsigned int	prog_size;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			source_code[MEM_SIZE];

}				t_player;

/*
** Main corewar structure
*/

typedef struct	s_corewar
{
	int				player_amount;
	t_player		player[MAX_PLAYERS];
	t_args			args;
	unsigned char	arena[MEM_SIZE];
	// t_carriage		*head;
	// t_comms			p_tab[17];
	// unsigned int	cursors;
	// unsigned int	cycle;
	// unsigned int	tot_cycle;
	// unsigned int	cycles_to_die;
	// unsigned int	lives;
	// unsigned int	check;
	// unsigned int	bonus;
	// unsigned int	winner;
	// unsigned int	last_alive;
	char		**files;

}				t_vm;

/*
** Functions that represents parts of the program
*/

void			fill_the_map(t_vm *);

/*
** Utils
*/

bool			put_usage(const int);
int				meta_reader(const int, void *, const int);
void			meta_printer(const void *, const int);
unsigned int	read_raw_num(const int, const int);

#endif
