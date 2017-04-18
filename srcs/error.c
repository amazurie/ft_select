/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:15:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 13:20:22 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
