/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 12:34:50 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		winsize_changed(int sig)
{
	display_args(NULL);
}

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

	d = get_data(NULL);
	signal(SIGTSTP, &do_pause);
	signal(SIGCONT, &do_restart);
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	winsize_changed(0);
	user_hand(&d);
}

static void	sighandler(int sig)
{
	reset_term(get_data(NULL));
	exit(1);
}

int		main(int ac, char **av)
{
	t_data			*d;
	char			*name_term;

	if (!av || !av[1])
		disp_error("ft_select: bad input\nusage: ./ft_select input [input...]\n");
	if (!(name_term = getenv("TERM")))
		disp_error("No terminal specified, specify it with: 'setenv TERM'\n");
	d = (t_data *)ft_memalloc(sizeof(t_data));
	if (tgetent(NULL, name_term) == ERR || tcgetattr(0, &d->oldterm) == -1)
		print_error(NULL);
	tcgetattr(0, &d->term);
	d->term.c_lflag &= ~(ECHO | ICANON);
	d->term.c_cc[VMIN] = 1;
	d->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	signal(SIGTSTP, &do_pause);
	signal(SIGCONT, &do_restart);
	signal(SIGINT, sighandler);
	signal(SIGWINCH, &winsize_changed);
	d->args = char_to_lst(av);
	d->ac = ac - 2;
	d->num_curr = 0;
	get_data(d);
	ft_putstr_fd(tgetstr("ti", NULL), tty_fd(0));
	user_hand(&d);
	free_args(d->args);
	reset_term(d);
	return (0);
}
