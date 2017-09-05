/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/24 16:38:45 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		winsize_changed(int sig)
{
	t_data	*d;

	d = get_data(NULL);
	d->nbr_line = 0;
	d->nbr_col = 0;
	d->min_line = 0;
	display_args(d);
	if (d->line)
		disp_search(d->line);
	sig = 0;
}

static void	sighandler(int sig)
{
	reset_term(get_data(NULL));
	exit(sig);
}

static void	set_sig(void)
{
	int	i;

	i = 0;
	while (++i < 31)
	{
		if (i != 28)
			signal(i, sighandler);
	}
}

static int	test_term(void)
{
	char			*name_term;

//	name_term = "xterm";
	if (tgetent(NULL, name_term) == ERR)
	{
		name_term = getenv("TERM");
		if (!name_term[0] || tgetent(NULL, name_term) == ERR)
			return (-1);
		if (!tgetstr("cm", NULL) || !tgetstr("dl", NULL)
			|| !tgetstr("cd", NULL) || !tgetstr("ve", NULL)
			|| !tgetstr("te", NULL) || !tgetstr("ti", NULL)
			|| !tgetstr("vi", NULL) || !tgetstr("us", NULL)
			|| !tgetstr("mr", NULL) || !tgetstr("me", NULL)
			|| !tgetstr("md", NULL))
		{
			ft_putstr(ERR_COLOR);
			ft_putstr("Conflicting TERM defined, unload TERM, press any key\n");
			ft_putstr(DEFAULT_COL);
			tgetent(NULL, "");
			return (-2);
		}
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_data			*d;

	if (!av || !av[1])
		disp_error(
			"ft_select: bad input\nusage: /ft_select input [input...]\n");
	if (!(d = (t_data *)ft_memalloc(sizeof(t_data))))
		disp_error("malloc");
	tcgetattr(0, &d->oldterm);
	is_term(test_term());
	tcgetattr(0, &d->term);
	d->term.c_lflag &= ~(ECHO | ICANON);
	d->term.c_cc[VMIN] = 1;
	d->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	set_sig();
	if (is_term(0) == -2)
		read(0, av[0], 7);
	if (is_term(0) == -2)
		is_term(-1);
	signal(SIGWINCH, &winsize_changed);
	d->args = char_to_lst(av);
	d->ac = ac - 2;
	user_hand(&d);
	return (0);
}
