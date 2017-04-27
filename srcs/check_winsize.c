/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_winsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:42:31 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:01:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_up(int num_curr, int max_col, int *whcl)
{
	int	i;
	int	j;

	j = max_col;
	while (j-- > 0)
	{
		i = 0;
		while (i < whcl[3])
		{
			if (num_curr >= j + whcl[4] * i
					&& num_curr < j + whcl[4] * i + whcl[1])
				return (j);
			i++;
		}
	}
	return (0);
}

static int	check_down(int num_curr, int max_col, int *whcl)
{
	int	i;
	int	j;

	j = max_col;
	while (j++ < whcl[4] - whcl[1])
	{
		i = 0;
		while (i < whcl[3])
		{
			if (num_curr >= j + whcl[4] * i
					&& num_curr < j + whcl[4] * i + whcl[1])
				return (j);
			i++;
		}
	}
	return (0);
}

int			check_winsize(t_data *d, int *whcl)
{
	t_arg	*arg;
	int		i;
	int		j;

	arg = d->args;
	while (arg)
	{
		arg = arg->next;
		i++;
	}
	if (whcl[3] * whcl[1] >= i)
		return (0);
	i = 0;
	j = d->max_col;
	while (i < whcl[3])
	{
		if (d->num_curr >= j + whcl[4] * i
				&& d->num_curr < j + whcl[4] * i + whcl[1])
			return (j);
		i++;
	}
	if ((i = check_down(d->num_curr, d->max_col, whcl)) > 0)
		return (i);
	return (i = check_up(d->num_curr, d->max_col, whcl));
}
