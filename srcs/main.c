/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/14 14:33:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		sighandler(int sig)
{
	if (sig == SIGINT || sig == SIGTSTP || sig == SIGINT
		|| sig == SIGINT || sig == SIGHUP || sig == SIGTERM
		|| sig == SIGSEGV || sig == SIGQUIT || sig == SIGFPE
		|| sig == SIGALRM || sig == SIGKILL || sig == SIGABRT
		|| sig == SIGUSR1 || sig == SIGUSR2)
	{
		reset_term(get_data(NULL));
		exit(1);
	}
	else if (sig == SIGCONT)
		;
}

void		winsize_changed(int sig)
{
	display_args(NULL);
}

int		in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
		return (0);
	else if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if ((tmp[0] == 127 && !tmp[1])
		|| (tmp[0] == 27 && tmp[1] == 91
		&& tmp[2] == 51 && tmp[3] == 126))
		do_del(d);
	else if (tmp[0] == 27 && tmp[1] == 91)
		return (gest_arrow(d, tmp));
	else
		return (1);
	return (2);
}

static void	user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	ft_putstr_fd(tgetstr("ti", NULL), tty_fd());
	write(tty_fd(), tgetstr("vi", NULL), 6);
	tmp = (char *)ft_memalloc(7);
	i = 2;
	while (i)
	{
		if (i == 2)
			display_args(*d);
		read(0, tmp, 6);
//		i = 0;
//		while (tmp[i])
//			printf("%i\n", tmp[i++]);
		i = in(d, tmp);
		get_data(*d);
		ft_bzero(tmp, 6);
		if (!(*d)->args)
			i = 0;
	}
}

int			main(int ac, char **av)
{
	t_data			*d;
	char			*name_term;

	if (!av || !av[1])
		disp_error("ft_select: bad input\nusage: ./ft_select input [input...]\n");
	if (!(name_term = getenv("TERM")))
		disp_error("No terminal specified, specify it with: 'setenv TERM'\n");
	d = (t_data *)ft_memalloc(sizeof(t_data));
	if (tgetent(NULL, name_term) == ERR
			|| tcgetattr(0, &d->oldterm) == -1)
		print_error(NULL);
	tcgetattr(0, &d->term);
	d->term.c_lflag &= ~(ECHO | ICANON);
	d->term.c_cc[VMIN] = 1;
	d->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	signal(SIGINT, sighandler);
	signal(SIGWINCH, &winsize_changed);
	d->args = char_to_lst(av);
	d->ac = ac - 2;
	d->num_curr = 0;
	get_data(d);
	user_hand(&d);
	reset_term(d);
}
