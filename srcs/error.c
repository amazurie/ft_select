/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:15:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:37:51 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		print_errorcont(char *str)
{
	struct winsize	w;
	t_data			*d;
	static char		*s = NULL;

	if (str != NULL)
		s = str;
	if (!s)
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	ft_putstr_fd(ERR_COLOR, tty_fd(0));
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, w.ws_col), tty_fd(0));
	ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
	ft_putstr_fd(s, tty_fd(0));
	ft_putstr_fd(DEFAULT_COL, tty_fd(0));
	if (str == NULL)
		s = NULL;
	return (0);
}

void	print_error(char *str)
{
	t_data	*d;

	perror(str);
	d = get_data(NULL);
	if (d)
	{
		tcsetattr(0, 0, &d->oldterm);
		reset_term(d);
		free(d);
	}
	exit(1);
}

void	disp_error(char *str)
{
	t_data	*d;

	ft_putstr_fd(str, 2);
	d = get_data(NULL);
	if (d)
		reset_term(d);
	exit(1);
}
