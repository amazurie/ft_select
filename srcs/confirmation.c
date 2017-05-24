/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirmation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:08:18 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 13:08:19 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		confirm(char *s)
{
	struct winsize	w;
	char			*tmp;

	tmp = (char *)ft_memalloc(7);
	while (tmp[0] != 89 && tmp[0] != 121 && tmp[0] != 110
			&& tmp[0] != 78 && tmp[0] != 10 && tmp[0] != 27)
	{
		ioctl(0, TIOCGWINSZ, &w);
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, w.ws_col), tty_fd(0));
		ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
		ft_putstr_fd(s, tty_fd(0));
		ft_putstr_fd(" continue ? (y/n) ", tty_fd(0));
		read(0, tmp, 6);
	}
	if (tmp[0] == 89 || tmp[0] == 121 || tmp[0] == 10)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
