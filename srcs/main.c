/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/29 14:13:37 by amazurie         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		reset_term(get_data(NULL));
		exit(1);
	}
}

int			main(int ac, char **av)
{
	t_data			*d;
	char			*name_term;

	if (!av || !av[1])
		disp_error(
				"ft_select: bad input\nusage: /ft_select input [input...]\n");
	if (!(name_term = getenv("TERM")))
		name_term = "xterm";
	if (tgetent(NULL, name_term) == ERR || tcgetattr(0, &d->oldterm) == -1)
		disp_error("could not load TERM! specify it with: 'setenv TERM'\n");
	if (!(d = (t_data *)ft_memalloc(sizeof(t_data))))
		disp_error("malloc");
	tcgetattr(0, &d->term);
	d->term.c_lflag &= ~(ECHO | ICANON);
	d->term.c_cc[VMIN] = 1;
	d->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &d->term) == -1)
		print_error(NULL);
	signal(SIGWINCH, &winsize_changed);
	d->args = char_to_lst(av);
	d->ac = ac - 2;
	signal(SIGINT, sighandler);
	user_hand(&d);
	return (0);
}
