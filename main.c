/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 21:53:26 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/04 17:03:05 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int		fd[100];
	int		mul = 1;
	char	*sep = "\n";
	int		i;
	int		n;
	int		last;
	char	*buf;
	int		err;
	int		files;
	int		alt = 0;
	int		alldone = 0;

	ft_putendl(av[0]);
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-mul"))
			mul = ft_atoi(av[++i]);
		else if (!ft_strcmp(av[i], "-sep"))
			sep = av[++i];
		else if (!ft_strcmp(av[i], "-alt"))
			alt = 1;
		else
			break;
	}
	ft_putstr("sep is ");
	ft_putendl(sep);
	ft_putstr("mul is ");
	ft_putnbr(mul);
	ft_putchar('\n');
	files = ac - i;
	last = i;
	i = 0;
	if (alt)
	{
		n = 0;
		while (n < mul)
		{
			i = 0;
			while (i < files)
			{
				fd[i] = open(av[last + i], O_RDONLY);
				++i;
			}
			alldone = 1;
			while (alldone)
			{
				alldone = 0;
				i = 0;
				while (i < files)
				{
					if (get_next_line(fd[i], &buf) > 0)
					{
						ft_putstr(buf);
						ft_putstr(sep);
						alldone = 1;
					}
					++i;
				}
			}
			++n;
		}
	}
	else
		while (i < files)
		{
			n = 0;
			while (n < mul)
			{
				ft_putendl(av[last + i]);
				fd[0] = open(av[last + i], O_RDONLY);
				while ((err = get_next_line(fd[0], &buf)) > 0)
				{
					ft_putstr(buf);
					ft_putstr(sep);
				}
				ft_putnbr(err);
				ft_putendl(" done");
				close(fd[0]);
				++n;
			}
			++i;
		}
	return (0);
}
