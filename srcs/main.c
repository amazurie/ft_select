/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:10:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		winsize_changed(int sig)
{
	display_args(NULL);
	sig = 0;
}

static void	sighandler(int sig)
{
	reset_term(get_data(NULL));
	sig = 0;
	exit(1);
}

int			main(int ac, char **av)
{
	t_data			*d;
	char			*name_term;

	if (!av || !av[1])
		disp_error(
				"ft_select: bad input\nusage: /ft_select input [input...]\n");
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
	signal(SIGWINCH, &winsize_changed);
	d->args = char_to_lst(av);
	d->ac = ac - 2;
	d->min_line = 0;
	d->num_curr = 0;
	signal(SIGINT, sighandler);
	user_hand(&d);
	return (0);
}
