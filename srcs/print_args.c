/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:24:13 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 13:24:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_args(t_data *d)
{
	t_arg	*arg;
	char	*buff;

	arg = d->args;
	buff = (char *)ft_memalloc(BUFF_SIZE + 1);
	while (arg)
	{
		if (arg->is_select)
		{
			buffcat(&buff, arg->elem);
			buffcat(&buff, " ");
		}
		arg = arg->next;
	}
	reset_term(get_data(NULL));
	ft_putstr(buff);
	exit(1);
}
