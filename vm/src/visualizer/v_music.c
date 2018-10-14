/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_music.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 23:46:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/15 00:35:02 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		init(t_vm *v)
{
	char			*pref;

	if (M.is_venom)
	{
		pref = "venom/";
	}
	else if (M.is_skibidi)
	{
		pref = "skibidi/";
	}
	else
	{
		pref = NULL;
	}
	pref = ft_strjoin("afplay music/", pref);
	M.play_start = ft_strjoin(pref, "start.mp3 &");
	M.play_die = ft_strjoin(pref, "die.mp3 &");
	M.play_end = ft_strjoin(pref, "end.mp3 &");
	free(pref);
}

void					play_music(t_vm *v, int flag, bool is_allocate)
{
	if (is_allocate)
		init(v);
	if (M.playing + M.to_wait - 1 < time(NULL))
	{
		if (flag == MSTART)
		{
			if (system(M.play_start) == 0)
				M.to_wait = (M.is_venom) ? VENOM_START_DUR : SKIBIDI_START_DUR;
			M.playing = time(NULL);
		}
		else if (flag == MDIE)
		{
			if (system(M.play_die) == 0)
				M.to_wait = (M.is_venom) ? VENOM_DIE_DUR : SKIBIDI_DIE_DUR;
			M.playing = time(NULL);
		}
		else if (flag == MEND)
		{
			system("pkill afplay");
			system(M.play_end);
		}
	}
}
