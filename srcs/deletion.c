/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:15:23 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 15:37:02 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		del_arg(t_data **d, t_arg **arg, t_arg **tmp)
{
	if (!(*tmp))
	{
		(*tmp) = (*arg);
		(*arg) = (*arg)->next;
		(*d)->args = (*arg);
		free((*tmp)->elem);
		free((*tmp));
		(*tmp) = NULL;
	}
	else
	{
		(*tmp)->next = (*arg)->next;
		free((*arg)->elem);
		free((*arg));
		(*arg) = (*tmp)->next;
	}
}

static void	check_del(t_data **d, t_arg **arg, t_arg **tmp)
{
	if ((*arg)->is_select && (*arg)->num == (*d)->num_curr)
		(*d)->num_curr++;
	if ((*arg)->is_select)
		del_arg(d, arg, tmp);
	else
	{
		if ((*arg)->num == (*d)->num_curr)
			(*arg)->is_select = 1;
		(*tmp) = (*arg);
		(*arg) = (*arg)->next;
	}
}

void		do_del(t_data **d)
{
	t_arg	*arg;
	t_arg	*tmp;

	tmp = NULL;
	arg = (*d)->args;
	while (arg)
		check_del(d, &arg, &tmp);
	reset_num(d);
	arg = (*d)->args;
	if (!arg)
		return ;
	while (arg && !arg->is_select)
		arg = arg->next;
	arg->is_select = 0;
	(*d)->num_curr = arg->num;
}

void		del_curr(t_data **d)
{
	t_arg	*tmp;
	t_arg	*tmp2;

	if ((*d)->conf_mode == 2 && !confirm("this will delete current argument"))
		return ;
	tmp = (*d)->args;
	tmp2 = NULL;
	while (tmp)
	{
		if (tmp->num == (*d)->num_curr)
		{
			del_arg(d, &tmp, &tmp2);
			reset_num(d);
			if ((*d)->num_curr > (*d)->ac)
				(*d)->num_curr = 0;
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void		free_args(t_arg **arg)
{
	t_arg	*tmp;

	while (arg && *arg)
	{
		tmp = *arg;
		free(tmp->elem);
		*arg = (*arg)->next;
		free(tmp);
	}
	free(*arg);
	*arg = NULL;
}
