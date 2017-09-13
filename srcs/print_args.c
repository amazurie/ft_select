/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:24:13 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:50:43 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_args(t_data *d)
{
	t_arg	*arg;
	char	*buff;
	int		i;

	if (d->conf_mode == 2 && !confirm("you will confirm your selection"))
		return ;
	arg = d->args;
	if (!(buff = (char *)ft_memalloc(BUFF_SIZE + 1)))
		print_error("malloc");
	i = 1;
	while (arg)
	{
		if (arg->is_select)
		{
			if (i != 1)
				buffcat(&buff, " ");
			buffcat(&buff, arg->elem);
			i = 0;
		}
		arg = arg->next;
	}
	reset_term(get_data(NULL));
	ft_putstr(buff);
	exit(1);
}
