/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:37:14 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 13:12:53 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		select_all(t_data **d, int etat)
{
	t_arg	*tmp;

	if (etat)
		etat = 1;
	else
		etat = 0;
	if (etat == 1)
	{
		if (!confirm("All arguments will be selected"))
			return ;
	}
	else if (!confirm("All arguments will be unselected"))
		return ;
	tmp = (*d)->args;
	while (tmp)
	{
		tmp->is_select = etat;
		tmp = tmp->next;
	}
}
