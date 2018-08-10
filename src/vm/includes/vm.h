/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/07 20:24:42 by vbrazas          ###   ########.fr       */
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
	bool			is_alive;
	char			*filename;
	unsigned int	magic;
	unsigned int	prog_size;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			source_code[MEM_SIZE];

}				t_player;

/*
** Carriage structure
** unsigned char	*where;	// iterator of the v->arena
** int				whom;	// index of the v->players
*/

typedef struct s_carriage					t_car;
typedef struct s_carriage_virtual_table		t_car_vt;

struct			s_carriage
{
	int				whom;
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	unsigned char	*pc;
	bool			carry;
	t_car			*prev;
	t_car			*next;

	t_car_vt		vt;

};

struct			s_carriage_virtual_table
{
	void		(*perform_next_comm)(t_car *self);
};

/*
** Main corewar structure
*/

typedef struct	s_corewar
{
	int				player_amount;
	t_player		player[MAX_PLAYERS];
	t_args			args;

	unsigned char	arena[MEM_SIZE];
	t_car			*head;


	// t_comms			p_tab[REG_NUMBER];

	// unsigned int	cursors;
	// unsigned int	cycle;
	// unsigned int	tot_cycle;
	// unsigned int	cycles_to_die;
	// unsigned int	lives;
	// unsigned int	check;
	// unsigned int	bonus;
	// unsigned int	winner;
	// unsigned int	last_alive;

}				t_vm;

/*
** Functions that represents parts of the program
*/

void			fill_players(t_vm *v);
void			fill_arena(t_vm *v);
void			print_arena_to_stdout(t_vm *v);
void			open_files(int ac, char **av, t_vm *v, int i);
void			check_and_obtain_args(int ac, char **av, t_vm *v);

/*
** Carriage related functions
*/

t_car			*get_last_car(t_vm *v);
void			init_car(unsigned char *where, int whom, t_vm *v);
void			init_car_vt(t_car *car);

/*
** Utils
*/

int				meta_reader(const int fd, void *read_in, const int nbytes);
void			meta_printer(const void *to_print, const int nbytes);
unsigned int	read_raw_num(const int fd, const int chars_to_read);

/*
** Put Error functions
*/

bool			put_usage(const int errnum);
bool			put_error(const int errnum, const char *errstr,
	const int i1, const int i2);

#endif
