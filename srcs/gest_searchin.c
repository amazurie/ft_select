/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_searchin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 14:24:18 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 12:04:31 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	del_beg(t_data **d, char *line)
{
	t_arg	*arg;
	t_arg	*tmp;

	tmp = NULL;
	arg = (*d)->args;
	while (arg)
	{
		if (arg->is_select && arg->num == (*d)->num_curr)
			(*d)->num_curr++;
		if (ft_strncmp(arg->elem, (line + 1), ft_strlen((line + 1))) == 0)
			del_arg(d, &arg, &tmp);
		else
		{
			if (arg->num == (*d)->num_curr)
				arg->is_select = 1;
			tmp = arg;
			arg = arg->next;
		}
	}
	reset_num(d);
	arg = (*d)->args;
	if (!arg)
		return ;
	(*d)->num_curr = arg->num;
}

static void	select_beg(t_data **d, char *line, int etat)
{
	t_arg *tmparg;

	if (etat)
		etat = 1;
	else
		etat = 0;
	if (etat == 1)
	{
		if ((*d)->conf_mode > 0
			&& !confirm("All arguments begin with search will be selected"))
			return ;
	}
	else if ((*d)->conf_mode > 0
			&& !confirm("All arguments begin with search will be unselected"))
		return ;
	tmparg = (*d)->args;
	while (tmparg)
	{
		if (ft_strncmp(tmparg->elem, (line + 1), ft_strlen((line + 1))) == 0)
			tmparg->is_select = etat;
		tmparg = tmparg->next;
	}
}

int			gest_searchin(t_data **d, char *line, char *tmp)
{
	if (tmp[0] == 1 && !tmp[1])
		select_beg(d, line, 1);
	else if (tmp[0] == 21 && !tmp[1])
		select_beg(d, line, 0);
	else if (tmp[0] == 27 && tmp[1] == 91
			&& tmp[2] == 51 && tmp[3] == 126)
	{
		if ((*d)->conf_mode == 0
			|| confirm("All arguments begin with search will be deleted"))
			del_beg(d, line);
	}
	else
		return (0);
	display_args(*d);
	return (1);
}
