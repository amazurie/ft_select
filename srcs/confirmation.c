/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirmation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:08:18 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/24 11:28:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	conf_mode(t_data **d, int mode)
{
	struct winsize	w;
	int				j;

	if (mode == 1)
		(*d)->conf_mode = ((*d)->conf_mode - 1 < 0) ? 2 : (*d)->conf_mode - 1;
	else if (mode == 2)
		(*d)->conf_mode = ((*d)->conf_mode + 1 > 2) ? 0 : (*d)->conf_mode + 1;
	j = (ioctl(0, TIOCGWINSZ, &w) != -1) ? w.ws_col - 17 : -1;
	if (j < 0)
		return ;
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), j, w.ws_row), tty_fd(0));
	ft_putstr_fd(tgetstr("dl", NULL), tty_fd(0));
	print_errorcont(NULL);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), j, w.ws_row), tty_fd(0));
	ft_putstr_fd(CONF_COL, tty_fd(0));
	ft_putstr_fd("confirm: ", tty_fd(0));
	ft_putstr_fd(DEFAULT_COL, tty_fd(0));
	if ((*d)->conf_mode == 0)
		ft_putstr_fd("none", tty_fd(0));
	else if ((*d)->conf_mode == 1)
		ft_putstr_fd("default", tty_fd(0));
	else if ((*d)->conf_mode == 2)
		ft_putstr_fd("all", tty_fd(0));
	(is_term(0) < 0) ? ft_putstr_fd("\n", tty_fd(0)) : 0;
}

int		confirm(char *s)
{
	struct winsize	w;
	char			*tmp;

	if (!(tmp = (char *)ft_memalloc(7)))
		return (print_errorcont("allocation error, confirmation pass") + 1);
	while (tmp[0] != 89 && tmp[0] != 121 && tmp[0] != 110
			&& tmp[0] != 78 && tmp[0] != 10 && tmp[0] != 27)
	{
		ioctl(0, TIOCGWINSZ, &w);
		ft_putstr_fd(CONF_COL, tty_fd(0));
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, w.ws_col), tty_fd(0));
		ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
		ft_putstr_fd(s, tty_fd(0));
		ft_putstr_fd(", continue ? (y/n) ", tty_fd(0));
		ft_putstr_fd(DEFAULT_COL, tty_fd(0));
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
