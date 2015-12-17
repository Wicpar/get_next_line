/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 06:02:26 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/17 21:51:55 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char		**getbuflines(int fd)
{
	int		i;
	size_t	n;
	char	buf[BUFF_SIZE + 1];
	char	**tmp;

	n = 0;
	while (n < BUFF_SIZE && (i = read(fd, &buf[n], BUFF_SIZE - n)) && (n += i))
		if (i < 0)
			return ((char**)1);
		else if (i == 0)
			return (0);
	i = 2;
	n = -1;
	while (++n && buf[n])
		if (buf[n] == '\n')
			buf[n] = !(++i);
	tmp = (char**)ft_memalloc(sizeof(char*) * i);
	n = 0;
	i = -1;
	while (n < BUFF_SIZE)
	{
		tmp[++i] = ft_strdup(&buf[n]);
		n += ft_strchr(&buf[n] + 1, 0) - &buf[n];
	}
	return (tmp);
}

static t_list	*addinfo(int const fd, t_list **fds)
{
	t_fdinfo	info;
	t_list		*tmp;

	info.fd = fd;
	info.buf = getbuflines(fd);
	ft_lstadd(fds, tmp = ft_lstnew(&info, sizeof(t_fdinfo)));
	return (tmp);
}

static int		handle(t_fdinfo *info, char **line)
{
	char	*tmp;
	char	**buf;
	size_t	bufsize;

	buf = info->buf;
	*line = buf[0];
	while (buf[1] == 0)
	{
		free(buf);
		buf = getbuflines(info->fd);
		if (buf <= (char**)1)
			return (-((int)buf));
		tmp = *line;
		*line = ft_strjoin(tmp, buf[0]);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&buf[0]);
	}
	bufsize = 1;
	while (buf[bufsize])
		++bufsize;
	ft_memmove(&buf[0], &buf[1], bufsize + 1);
	info->buf = buf;
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*fds[1];
	size_t			tmp;
	t_list			*info;
	t_fdinfo		*elem;
	char			*new;

	if (fd < 0 || BUFF_SIZE < 1)
		return (-1);
	info = *fds;
	while (info)
	{
		if (((t_fdinfo*)info->content)->fd == fd)
			break;
		info = info->next;
	}
	if (!info && !(info = addinfo(fd, fds)))
		return (-1);
	elem = (t_fdinfo*)info->content;
	if (elem->buf)
		return (handle(elem, line));
	else
		return (-1);
}
