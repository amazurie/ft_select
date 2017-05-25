/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:37:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:13:08 by amazurie         ###   ########.fr       */
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

static int	in2(t_data **d, char *tmp)
{
	if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if (tmp[0] == 27 && tmp[1] == 91 && (tmp[2] == 72
			|| tmp[2] == 70) && !tmp[3])
	{
		if (tmp[2] == 72)
			(*d)->num_curr = 0;
		else if (tmp[2] == 70)
			(*d)->num_curr = (*d)->ac;
		display_args(*d);
	}
	else if (tmp[0] == 27 && tmp[1] == 91)
		gest_arrow(d, tmp);
	else if ((tmp[0] == 10) && !tmp[1])
	{
		print_args(*d);
		reset_term(*d);
		exit(1);
	}
	return (1);
}

static int	in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
	{
		reset_term(*d);
		exit(1);
	}
	else if ((tmp[0] == 127 && !tmp[1])
			|| (tmp[0] == 27 && tmp[1] == 91
				&& tmp[2] == 51 && tmp[3] == 126))
		do_del(d);
	else if ((tmp[0] == 65 || tmp[0] == 97) && !tmp[1])
		select_all(d, 1);
	else if ((tmp[0] == 85 || tmp[0] == 117) && !tmp[1])
		select_all(d, 0);
	else if (tmp[0] == 47 && !tmp[1])
		search(d);
	else if ((tmp[0] == 68 || tmp[0] == 100) && !tmp[1])
		del_curr(d);
	else
		return (in2(d, tmp));
	return (2);
}

void		user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	ft_putstr_fd(tgetstr("ti", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	tmp = (char *)ft_memalloc(7);
	signal(SIGTSTP, &do_pause);
	signal(SIGCONT, &do_restart);
	(*d)->nbr_line = 0;
	(*d)->nbr_col = 0;
	i = 2;
	while (i)
	{
		get_data(*d);
		if (i == 2)
			display_args(*d);
		read(0, tmp, 6);
		i = in(d, tmp);
		ft_bzero(tmp, 6);
		if (!(*d)->args)
			i = 0;
	}
	free_args((*d)->args);
	reset_term((*d));
}
