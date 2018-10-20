/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_music.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 23:46:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/20 13:58:21 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline bool		init(t_vm *v)
{
	char			*pref;

	if (M.is_venom)
		pref = "venom/";
	else if (M.is_skibidi)
		pref = "skibidi/";
	else
		pref = NULL;
	pref = ft_strjoin("afplay $HOME/projects/corewar/vm/music/", pref);
	M.play_start = ft_strjoin(pref, "start.mp3 &> /dev/null &");
	M.play_die = ft_strjoin(pref, "die.mp3 &> /dev/null &");
	M.play_end = ft_strjoin(pref, "end.mp3 &> /dev/null &");
	free(pref);
	return (true);
}

void					play_music(t_vm *v, int flag)
{
	static int		is_allocate = 0;

	if (is_allocate == 0)
		init(v) && ++is_allocate;
	if (M.playing + M.to_wait < time(NULL))
	{
		if (flag == MSTART)
		{
			system(M.play_start);
			M.to_wait = (M.is_venom) ? VENOM_START_DUR : SKIBIDI_START_DUR;
			M.playing = time(NULL);
		}
		else if (flag == MDIE)
		{
			system(M.play_die);
			M.to_wait = (M.is_venom) ? VENOM_DIE_DUR : SKIBIDI_DIE_DUR;
			M.playing = time(NULL);
		}
	}
	if (flag == MEND)
	{
		system("pkill afplay");
		system(M.play_end);
	}
}
