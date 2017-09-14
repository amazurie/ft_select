/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_onearg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 16:11:52 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_isscreen(t_data *d, t_arg *ar)
{
	struct winsize	ws;
	int				wcl[5];

	ioctl(tty_fd(0), TIOCGWINSZ, &ws);
	wcl[0] = ws.ws_row - 2;
	wcl[1] = nbrline(d->args, ws.ws_col, &wcl[2]);
	if (wcl[2] - 1 > ws.ws_col)
		return (0);
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
	if (wcl[4] == 0)
		return (0);
	return (1);
}

void		display_onearg(t_data *d, int num)
{
	t_arg			*ar;

	if (is_term(0) < 0)
	{
		display_args(d);
		return ;
	}
	ar = d->args;
	while (ar && ar->num != num)
		ar = ar->next;
	if (!ar || !check_isscreen(d, ar))
		return ;
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), ar->pos_y, ar->pos_x), tty_fd(0));
	if (ar->num == d->num_curr)
		ft_putstr_fd(tgetstr("us", NULL), tty_fd(0));
	if (ar->is_select)
		ft_putstr_fd(tgetstr("mr", NULL), tty_fd(0));
	ft_putstr_fd(ar->color, tty_fd(0));
	ft_putstr_fd(ar->elem, tty_fd(0));
	ft_putstr_fd(DEFAULT_COL, tty_fd(0));
	ft_putstr_fd(tgetstr("me", NULL), tty_fd(0));
}
