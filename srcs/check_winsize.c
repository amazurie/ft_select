/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_winsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:42:31 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:15:33 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_up(int num_curr, int min_line, int *whcl)
{
	int	i;
	int	j;

	j = min_line;
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

static int	check_down(int num_curr, int min_line, int *whcl)
{
	int	i;
	int	j;

	j = min_line;
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
	int		i;
	int		j;

	i = 0;
	j = d->min_line;
	while (i < whcl[3])
	{
		if (d->num_curr >= j + whcl[4] * i
				&& d->num_curr < j + whcl[4] * i + whcl[1])
			return (j);
		i++;
	}
	if ((i = check_down(d->num_curr, d->min_line, whcl)) > 0)
		return (i);
	return (i = check_up(d->num_curr, d->min_line, whcl));
}
