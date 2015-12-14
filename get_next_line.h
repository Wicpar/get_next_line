/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 06:03:38 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/14 21:43:23 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# include <string.h>
# define BUFF_SIZE 32

typedef	struct		s_fdinfo
{
	int				fd;
	char			**buf;
}					t_fdinfo;

#endif
