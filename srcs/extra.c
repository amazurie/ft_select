/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:35:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/14 12:41:26 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		check_winsize(t_arg *arg, char **buff, int *whcl)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (whcl[3] * whcl[4] < i || whcl[1] < whcl[4]
			|| whcl[0] < whcl[3] * whcl[2])
	{
		buffcat(buff, "Windows size too small, please increase size");
		return (0);
	}
	return (1);
}

int		tty_fd(void)
{
	static int	ttyfd = -1;

	if (ttyfd == -1)
		ttyfd = open("/dev/tty", O_RDWR);
	return (ttyfd);
}

t_data	*get_data(t_data *d)
{
	static t_data	*save_data = NULL;

	if (d)
		save_data = d;
	return (save_data);
}

void	print_error(char *str)
{
	t_data	*d;

	perror(str);
	d = get_data(NULL);
	if (d)
	{
		tcsetattr(0, 0, &d->oldterm);
		reset_term(d);
		free(d);
	}
	exit(1);
}

void	disp_error(char *str)
{
	t_data	*d;

	ft_putstr_fd(str, 2);
	d = get_data(NULL);
	if (d)
		reset_term(d);
	exit(1);
}

void	reset_term(t_data *d)
{
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd());
	ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	tcsetattr(0, 0, &d->oldterm);
	close(tty_fd());
}
