/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_colline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:43:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 16:59:52 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		nbrline(t_arg *arg, int w, int *len)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	*len = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->elem) >= (size_t)*len)
			*len = ft_strlen(tmp->elem) + 1;
		tmp = tmp->next;
		i++;
	}
	if (w > *len && i != 1)
		return (w / *len - (w % *len == 0));
	return (1);
}

int		nbr_col(t_arg *arg, int *nline)
{
	t_arg	*tmp;
	int		nbr;
	int		i;
	int		j;

	nbr = 0;
	tmp = arg;
	while (tmp)
	{
		tmp = tmp->next;
		nbr++;
	}
	i = 0;
	while (i * nbr < *nline)
		i++;
	j = nbr + (*nline - (i - 1) * nbr);
	i = 0;
	while (i * *nline < j)
		i++;
	i--;
	j = i + (i * *nline < nbr);
	*nline -= (i * *nline < nbr);
	return (i + (i * *nline < nbr));
}
