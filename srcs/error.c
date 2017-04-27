/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:15:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 16:39:44 by amazurie         ###   ########.fr       */
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
