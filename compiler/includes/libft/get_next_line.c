/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:44:25 by ndidenko          #+#    #+#             */
/*   Updated: 2018/02/27 17:44:26 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_myread(char **buff_static, int fd, int read_res)
{
	char		*buff;
	char		*tmp;

	if (*buff_static && ft_strchr(*buff_static, '\n'))
		return (-3);
	buff = ft_strnew(BUFF_SIZE);
	while ((read_res = read(fd, buff, BUFF_SIZE)))
	{
		if (read_res < 0)
			return (-1);
		buff[read_res] = '\0';
		tmp = *buff_static;
		*buff_static = ft_strjoin(*buff_static, buff);
		free(tmp);
		if (ft_strchr(*buff_static, '\n'))
			break ;
	}
	free(buff);
	if (*buff_static && **buff_static == 0)
		return (0);
	if (*buff_static && !(ft_strchr(*buff_static, '\n')))
		return (-2);
	if (*buff_static && ft_strchr(*buff_static, '\n'))
		return (-3);
	return (0);
}

static	int		ft_without_n(char **buff_static, char **line)
{
	int			len;
	char		*tmpbuff;

	tmpbuff = *buff_static;
	len = ft_strlen(*buff_static);
	*line = ft_strsub(*buff_static, 0, len);
	*buff_static = ft_strdup(*buff_static + len);
	free(tmpbuff);
	return (1);
}

static	int		ft_with_n(char **buff_static, char **line)
{
	int			len;
	char		*tmpbuff;

	tmpbuff = *buff_static;
	len = ft_strchr(*buff_static, '\n') - *buff_static;
	*line = ft_strsub(*buff_static, 0, len);
	*buff_static += 1;
	*buff_static = ft_strdup(*buff_static + len);
	free(tmpbuff);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*buff_static[FD_MAX];
	int			myread_res;
	int			read_res;

	read_res = 0;
	if (line == NULL || fd < 0 || BUFF_SIZE < 1 || read(fd, 0, 0))
		return (-1);
	myread_res = ft_myread(&buff_static[fd], fd, read_res);
	if (myread_res == -2)
		return (ft_without_n(&buff_static[fd], line));
	if (myread_res == -3)
		return (ft_with_n(&buff_static[fd], line));
	if (myread_res == -1)
		return (-1);
	return (0);
}
