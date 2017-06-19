/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:49:49 by amazurie         ###   ########.fr       */
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
	if (!(d = (t_data *)ft_memalloc(sizeof(t_data))))
		print_error("malloc");
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
