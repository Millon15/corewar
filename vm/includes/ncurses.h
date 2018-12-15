/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 07:04:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/12/15 19:13:48 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_H
# define NCURSES_H

/*
** Color pair defines
*/

# define BORDER						31
# define MAIN						32
# define INFO						33
# define COLOR_REDDY				34
# define COLOR_DARK					40
# define COLOR_ORANGE				41
# define STAT						42
# define COLOR_DELTA				10
# define CLR_CYCTOWAIT				50

/*
** ncurses visualizer info
*/

# define EXIT_KEY					27
# define RUN						' '
# define PASS_OVER					's'
# define RUN_SLOWER					'q'
# define RUN_QUICKER				'r'
# define RUN_SLOWER2				'w'
# define RUN_QUICKER2				'e'

# define BORDC						'*'
# define SQMAX_VAL					1000
# define TOT_LIVES_TERM				1000
# define SQBIG_VAL					10
# define SQSMALL_VAL				1
# define COLOR_AMOUNT				(MAX_PLAYERS + 1)
# define COMMON_HEIGHT				(MEM_SIZE / 64 + 4)
# define MW_WIDTH					(64 * 3 + 7)
# define IW_WIDTH					(MW_WIDTH / 3)
# define SW_WIDTH					(MW_WIDTH + IW_WIDTH - 1)
# define START_CYCLES_PER_SEC		50
# define START_ROW					2

# define ALIGN_CENTER(width, len)	(((width)-(len))?(((width)-(len))/2):0)

struct				s_widgets
{
	int				totliv_in_cp;
	int				totliv_in_lp;

	int				pval[MAX_PLAYERS];
	int				last_pval[MAX_PLAYERS];
};

struct				s_colors
{
	unsigned char	main;
	unsigned char	bold;
	unsigned char	undrln;
};

# define N			v->ncurses

struct				s_curses
{
	bool			is_run;
	char			c;
	int				cycpersec;
	clock_t			t;

	WINDOW			*mainw;
	WINDOW			*infow;
	WINDOW			*statw;

	t_colors		clr[MEM_SIZE];

	short			ccolors[COLOR_AMOUNT];
	short			pcolors[COLOR_AMOUNT];
	short			scolors[COLOR_AMOUNT];

	t_widgets		w;
};

void				visualize_the_game(t_vm *v);
void				init_windows(t_vm *v);
void				set_start_vis_cycle(t_vm *v);
void				put_car_color_to_arena(t_vm *v);
void				print_one_cycle(t_vm *v, const bool is_pass_cycle);
void				print_widgets(t_vm *v, int *row);
void				print_info(t_vm *v, const bool is_print_full_info);
void				print_stats(t_vm *v);
void				deinit_windows(t_vm *v);
void				put_border(WINDOW *win);
void				play_music(t_vm *v, int flag);

#endif
