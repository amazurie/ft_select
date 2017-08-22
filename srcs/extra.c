/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:35:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 15:55:13 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		reset_num(t_data **d)
{
	t_arg	*arg;
	int		i;

	if (!(*d)->args)
		return ;
	arg = (*d)->args;
	i = 0;
	while (arg)
	{
		arg->num = i;
		i++;
		arg = arg->next;
	}
	(*d)->ac = i - 1;
}

int			tty_fd(int i)
{
	static int	ttyfd = -1;

	if (ttyfd == -1)
		ttyfd = open("/dev/tty", O_WRONLY);
	if (i == -1)
		ttyfd = i;
	return (ttyfd);
}

t_data		*get_data(t_data *d)
{
	static t_data	*save_data = NULL;

	if (d)
		save_data = d;
	return (save_data);
}

void		reset_term(t_data *d)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), tty_fd(0));
	ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd(0));
	ft_putstr_fd(tgetstr("te", NULL), tty_fd(0));
	tcsetattr(0, 0, &d->oldterm);
	close(tty_fd(0));
	tty_fd(-1);
}
