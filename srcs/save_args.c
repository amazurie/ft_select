/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:00:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:53:44 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_arg	*args_cpy(t_arg *args)
{
	t_arg	*ar;
	t_arg	*artmp;
	t_arg	*tmpar;

	if (!args || !(ar = (t_arg *)ft_memalloc(sizeof(t_arg))))
		return (NULL);
	artmp = ar;
	while (args)
	{
		artmp->num = args->num;
		artmp->color = args->color;
		artmp->elem = ft_strdup(args->elem);
		artmp->is_select = args->is_select;
		if (!(artmp->next = (t_arg *)ft_memalloc(sizeof(t_arg))))
			return (NULL);
		tmpar = artmp;
		artmp = artmp->next;
		args = args->next;
	}
	free(artmp);
	tmpar->next = NULL;
	return (ar);
}

static void		do_saveload(t_data **d, t_arg **s_args, char *tmp)
{
	if (tmp[0] == 115 || tmp[0] == 83)
	{
		if ((*d)->conf_mode > 0 && !confirm("you will save current state"))
			return ;
		if (*s_args != NULL)
			free_args(s_args);
		if (!(*s_args = args_cpy((*d)->args)))
			print_errorcont("error cannot save, operation ignored");
	}
	else if ((tmp[0] == 114 || tmp[0] == 82) && s_args && *s_args != NULL)
	{
		if ((*d)->conf_mode > 0 && !confirm("you will load saved state"))
			return ;
		if ((*d)->args)
			free_args(&(*d)->args);
		(*d)->args = args_cpy(*s_args);
	}
}

t_arg			*save_args(t_data **d, char *tmp)
{
	static t_arg	*s_args = NULL;

	if (!d || !(*d))
		return (NULL);
	else if (!(*d) && !tmp)
	{
		free_args(&s_args);
		s_args = NULL;
		return (NULL);
	}
	else
		do_saveload(d, &s_args, tmp);
	return (s_args);
}
