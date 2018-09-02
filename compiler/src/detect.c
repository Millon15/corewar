/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:40:11 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:40:12 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_detect_command_i_tab(char *line)
{
	char		*ptr;
	int			i;
	int			len;
	char		*commandsp;

	i = 15;
	ptr = 0;
	while (i >= 0)
	{
		commandsp = ft_strjoin(g_operations[i].name, "\t");
		ptr = ft_strstr_d(line, commandsp);
		if (ptr != 0)
		{
			len = ft_strlen(commandsp);
			if (ft_strncmp(ptr, commandsp, len) == 0 && *(ptr - 1) != ':')
			{
				ft_strdel(&commandsp);
				return (i);
			}
		}
		i--;
		ft_strdel(&commandsp);
	}
	return (i);
}

int				ft_detect_command_i(char *line)
{
	char	*ptr;
	int		i;
	int		len;
	char	*commandsp;

	i = 15;
	ptr = 0;
	while (i >= 0)
	{
		commandsp = ft_strjoin(g_operations[i].name, " ");
		ptr = ft_strstr_d(line, commandsp);
		if (ptr != 0)
		{
			len = ft_strlen(commandsp);
			if (ft_strncmp(ptr, commandsp, len) == 0 && *(ptr - 1) != ':')
			{
				ft_strdel(&commandsp);
				return (i);
			}
		}
		i--;
		ft_strdel(&commandsp);
	}
	i = ft_detect_command_i_tab(line);
	return (i);
}

static char		*ft_detect_command_tab(char *line)
{
	char	*ptr;
	int		i;
	int		len;
	char	*commandsp;

	i = 15;
	ptr = 0;
	while (i >= 0)
	{
		commandsp = ft_strjoin(g_operations[i].name, "\t");
		ptr = ft_strstr_d(line, commandsp);
		if (ptr != 0)
		{
			len = ft_strlen(commandsp);
			if (ft_strncmp(ptr, commandsp, len) == 0 && *(ptr - 1) != ':'
										&& *(ptr - 1) != '_')
			{
				free(commandsp);
				return (ptr);
			}
		}
		i--;
		free(commandsp);
	}
	return (0);
}

char			*ft_detect_command(char *line)
{
	char	*ptr;
	int		i;
	int		len;
	char	*commandsp;

	i = 15;
	ptr = 0;
	while (i >= 0)
	{
		commandsp = ft_strjoin(g_operations[i].name, " ");
		ptr = ft_strstr_d(line, commandsp);
		if (ptr != 0)
		{
			len = ft_strlen(commandsp);
			if (ft_strncmp(ptr, commandsp, len) == 0 &&
						*(ptr - 1) != ':' && *(ptr - 1) != '_')
			{
				free(commandsp);
				return (ptr);
			}
		}
		i--;
		free(commandsp);
	}
	return (ft_detect_command_tab(line));
}

int				ft_detect_label(char *line)
{
	int i;

	i = 0;
	if (ft_strchr(line, LABEL_CHAR) == 0)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line && *line != '#' && *line != LABEL_CHAR)
	{
		if (ft_strchr(LABEL_CHARS, *line) == 0)
			return (0);
		line++;
		i++;
	}
	if (*line == LABEL_CHAR)
		return (i);
	else
		return (0);
}
