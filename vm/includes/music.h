/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 07:04:20 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 09:49:28 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUSIC_H
# define MUSIC_H

/*
** Music structure
*/

# define M				v->music
# define MSTART			1
# define MDIE			2
# define MEND			4

typedef struct			s_single_music_info
{
	unsigned char		start_duration;
	unsigned char		die_duration;
	char				*play_start;
	char				*play_die;
	char				*play_end;

}						t_smi;

struct					s_music
{
	unsigned char		music;
	unsigned char		to_wait;
	t_smi				*cmi;

	time_t				playing;
};

#endif
