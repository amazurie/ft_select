/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_onearg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:05:41 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_onearg(t_data *d, int num)
{
	struct winsize	ws;
	t_arg			*ar;
	int				wcl[5];

	ar = d->args;
	while (ar && ar->num != num)
		ar = ar->next;
	ioctl(tty_fd(0), TIOCGWINSZ, &ws);
	wcl[0] = ws.ws_row - 1;
	wcl[1] = nbrline(d->args, ws.ws_col, &wcl[2]);
	wcl[2] = nbr_col(d->args, &wcl[1]);
	wcl[3] = 0;
	wcl[4] = 0;
	while (wcl[3] < wcl[1])
	{
		if (ar->num >= d->min_line + wcl[2] * wcl[3]
			&& ar->num < d->min_line + wcl[2] * wcl[3] + wcl[0])
			wcl[4] = 1;
		wcl[3]++;
	}
	if (wcl[4] == 0)
		display_args(d);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), ar->pos_y, ar->pos_x), tty_fd(0));
	if (ar->num == d->num_curr)
		ft_putstr_fd(tgetstr("us", NULL), tty_fd(0));
	if (ar->is_select)
		ft_putstr_fd(tgetstr("mr", NULL), tty_fd(0));
	ft_putstr_fd(ar->color, tty_fd(0));
	ft_putstr_fd(ar->elem, tty_fd(0));
	ft_putstr_fd(DEF_COLOR, tty_fd(0));
	ft_putstr_fd(tgetstr("me", NULL), tty_fd(0));
}
