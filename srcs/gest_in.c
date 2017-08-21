/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:37:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/21 16:17:54 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	do_pause(int sig)
{
	t_data	*d;
	char	io[2];

	sig = 0;
	d = get_data(NULL);
	reset_term(d);
	signal(SIGTSTP, SIG_DFL);
	io[0] = d->term.c_cc[VSUSP];
	io[1] = 0;
	ioctl(0, TIOCSTI, io);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), tty_fd(0));
	ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
}

static void	do_restart(int sig)
{
	t_data	*d;

	sig = 0;
	d = get_data(NULL);
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	ft_putstr_fd(tgetstr("ti", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	winsize_changed(0);
	signal(SIGTSTP, &do_pause);
	signal(SIGCONT, &do_restart);
}

static int	inni(t_data **d, char *tmp, int i)
{
	get_data(*d);
	if (i == 3)
	{
		(*d)->nbr_line = 0;
		(*d)->nbr_col = 0;
		(*d)->min_line = 0;
	}
	if (i == 2 || i == 3)
		display_args(*d);
	conf_mode(d, 0);
	read(0, tmp, 6);
	i = in(d, tmp);
	ft_bzero(tmp, 6);
	if (!(*d)->args)
		i = 0;
	return (i);
}

void		user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	(*d)->min_line = 0;
	(*d)->num_curr = 0;
	ft_putstr_fd(tgetstr("ti", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	signal(SIGTSTP, &do_pause);
	signal(SIGCONT, &do_restart);
	(*d)->nbr_line = 0;
	(*d)->nbr_col = 0;
	(*d)->max_len = 0;
	(*d)->conf_mode = 1;
	get_data(*d);
	if (!(tmp = (char *)ft_memalloc(7)))
		return (print_error("malloc"));
	i = 2;
	while (i)
		i = inni(d, tmp, i);
	free_args(&(*d)->args);
	save_args(NULL, NULL);
	reset_term((*d));
}
