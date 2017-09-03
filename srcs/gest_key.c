/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:22:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 16:44:46 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	left_arrow(t_data **d)
{
	struct winsize	ws;
	int				wcl[3];

	ioctl(tty_fd(0), TIOCGWINSZ, &ws);
	wcl[0] = ws.ws_col;
	wcl[1] = nbrline((*d)->args, wcl[0], &wcl[2]);
	wcl[2] = nbr_col((*d)->args, &wcl[1]);
	if ((*d)->num_curr - wcl[2] < 0)
	{
		if (wcl[1] * wcl[2] - wcl[2] + (*d)->num_curr - 1 > (*d)->ac)
			(*d)->num_curr = wcl[1] * wcl[2] - wcl[2] * 2 + (*d)->num_curr - 1;
		else
			(*d)->num_curr = wcl[1] * wcl[2] - wcl[2] + (*d)->num_curr - 1;
		if (wcl[2] == 1)
			(*d)->num_curr++;
	}
	else
		(*d)->num_curr -= wcl[2];
}

static void	right_arrow(t_data **d)
{
	struct winsize	ws;
	int				wcl[3];

	ioctl(tty_fd(0), TIOCGWINSZ, &ws);
	wcl[0] = ws.ws_col;
	wcl[1] = nbrline((*d)->args, wcl[0], &wcl[2]);
	wcl[2] = nbr_col((*d)->args, &wcl[1]);
	if ((*d)->num_curr + wcl[2] > (*d)->ac)
	{
		(*d)->num_curr = (*d)->num_curr + wcl[2] - wcl[1] * wcl[2] + 1;
		while ((*d)->num_curr < 0)
			(*d)->num_curr += wcl[2];
		if ((*d)->num_curr > (*d)->ac || (*d)->num_curr < 0)
			(*d)->num_curr = (*d)->ac;
		if (wcl[2] == 1)
			(*d)->num_curr = 0;
	}
	else
		(*d)->num_curr += wcl[2];
}

void		gest_arrow(t_data **d, char *tmp)
{
	int				num;

	num = (*d)->num_curr;
	if (tmp[2] == 65 || (tmp[2] == 68 && is_term(0) < 0))
		(*d)->num_curr = ((*d)->num_curr == 0) ? (*d)->ac : (*d)->num_curr - 1;
	else if (tmp[2] == 66 || (tmp[2] == 67 && is_term(0) < 0))
		(*d)->num_curr = ((*d)->num_curr == (*d)->ac) ?
			(*d)->num_curr = 0 : (*d)->num_curr + 1;
	else if (tmp[2] == 67)
		right_arrow(d);
	else if (tmp[2] == 68)
		left_arrow(d);
	if (tgetstr("cm", NULL) != NULL)
		display_onearg(*d, num);
	display_onearg(*d, (*d)->num_curr);
}

void		do_space(t_data **d)
{
	t_arg	*arg;
	int		num;

	num = (*d)->num_curr;
	arg = (*d)->args;
	while (arg && arg->num != (*d)->num_curr)
		arg = arg->next;
	if (arg->num == (*d)->num_curr)
	{
		if (arg->is_select)
			arg->is_select = 0;
		else
			arg->is_select = 1;
	}
	(*d)->num_curr = ((*d)->num_curr == (*d)->ac) ?
	(*d)->num_curr = 0 : (*d)->num_curr + 1;
	display_onearg((*d), num);
	display_onearg((*d), (*d)->num_curr);
}
