/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 06:02:26 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/13 07:00:27 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

t_fdinfo	*addinfo(int const fd, t_fdinfo **fds)
{
	t_fdinfo	*tmp;
	size_t		i;

	tmp = (t_fdinfo*)malloc(sizeof(t_fdinfo));
	if (tmp)
	{
		tmp->i = 0;
		tmp->fd = fd;
		tmp->buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (tmp->buf)
		{
			i = 0;
			while (i <= BUFF_SIZE)
				tmp->buf[i++] = 0;
		}
		else
			return (0);
		tmp->next = *fds;
	}
	*fds = tmp;
	return (tmp);
}

void		reloadBuffer(t_fdinfo *info)
{
	size_t	i;
	size_t	j;

	info->i = 0;
	i = 0;
	while ((i = (i + (j = read(info->fd, &info->buf[i], BUFF_SIZE - i))))
			< BUFF_SIZE)
		if (j == 0)
			break;
	while (i < BUFF_SIZE)
		info->buf[i++] = 0;
}

int			get_next_line(int const fd, char **line)
{
	static t_fdinfo	*fds[1];
	size_t			tmp;
	t_fdinfo		*info;
	char			*new;

	info = *fds;
	while (info)
	{
		if (info->fd == fd)
			break;
		info = info->next;
	}
	if (!info && !(info = addinfo(fd, fds)))
		return (-1);
	if (info->i < BUFF_SIZE)

}


