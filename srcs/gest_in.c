/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:37:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 13:31:30 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	in2(t_data **d, char *tmp)
{
	if ((tmp[0] == 65 || tmp[0] == 97) && !tmp[1])
		select_all(d, 1);
	else if ((tmp[0] == 85 || tmp[0] == 117) && !tmp[1])
		select_all(d, 0);
	else if ((tmp[0] == 68 || tmp[0] == 100) && !tmp[1])
		del_curr(d);
	else
		return (1);
	return (2);
}

static int	in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
	{
		reset_term(*d);
		exit(1);
	}
	else if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if ((tmp[0] == 127 && !tmp[1])
			|| (tmp[0] == 27 && tmp[1] == 91
				&& tmp[2] == 51 && tmp[3] == 126))
		do_del(d);
	else if (tmp[0] == 27 && tmp[1] == 91)
		return (gest_arrow(d, tmp));
	else if ((tmp[0] == 10) && !tmp[1])
	{
		print_args(*d);
		reset_term(*d);
		exit(1);
	}
	else
		return (in2(d, tmp));
	return (2);
}

void		user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	(*d)->num_curr = 0;
	ft_putstr_fd(tgetstr("ti", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	tmp = (char *)ft_memalloc(7);
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
