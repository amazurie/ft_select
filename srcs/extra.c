/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:35:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 15:31:58 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	file_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (mode & S_IXUSR)
		return ('e');
	if (S_ISREG(mode))
		return ('-');
	return ('?');
}

char		*arg_color(char *av)
{
	struct stat	atr;

	lstat(av, &atr);
	if (file_type(atr.st_mode) == 'd')
		return ("\x1b[1;36m");
	if (file_type(atr.st_mode) == 'l')
		return ("\x1b[35m");
	if (file_type(atr.st_mode) == 'e')
		return ("\x1b[31m");
	return ("\x1b[39m");
}

int			tty_fd(int i)
{
	static int	ttyfd = -1;

	if (ttyfd == -1)
		ttyfd = open("/dev/tty", O_WRONLY);
	if (i == -1)
		ttyfd = i;
	return (ttyfd);
}

t_data		*get_data(t_data *d)
{
	static t_data	*save_data = NULL;

	if (d)
		save_data = d;
	return (save_data);
}

void		reset_term(t_data *d)
{
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("te", NULL), tty_fd(0));
	tcsetattr(0, 0, &d->oldterm);
	close(tty_fd(0));
	tty_fd(-1);
}
