/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:28:11 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 15:32:19 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	in3(t_data **d, char *tmp)
{
	if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if (tmp[0] == 27 && tmp[1] == 91 && (tmp[2] == 72
				|| tmp[2] == 70) && !tmp[3])
	{
		if (tmp[2] == 72)
			(*d)->num_curr = 0;
		else if (tmp[2] == 70)
			(*d)->num_curr = (*d)->ac;
		display_args(*d);
	}
	else if (tmp[0] == 27 && tmp[1] == 91)
		gest_arrow(d, tmp);
	else if ((tmp[0] == 10) && !tmp[1])
	{
		print_args(*d);
		reset_term(*d);
		exit(1);
	}
	else if (tmp[0] == 60 && !tmp[1])
		conf_mode(d, 1);
	else if (tmp[0] == 62 && !tmp[1])
		conf_mode(d, 2);
	return (1);
}

static int	in2(t_data **d, char *tmp)
{
	if ((tmp[0] == 127 && !tmp[1])
			|| (tmp[0] == 27 && tmp[1] == 91
				&& tmp[2] == 51 && tmp[3] == 126))
	{
		if ((*d)->conf_mode != 2 || confirm("delete all selected argument"))
			do_del(d);
	}
	else if ((tmp[0] == 68 || tmp[0] == 100) && !tmp[1])
		del_curr(d);
	else if ((tmp[0] == 82 || tmp[0] == 83 || tmp[0] == 114 || tmp[0] == 115)
			&& !tmp[1])
		save_args(d, tmp);
	else
		return (in3(d, tmp));
	return (3);
}

int			in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
	{
		if ((*d)->conf_mode == 2 && !confirm("you will quit"))
			return (1);
		reset_term(*d);
		exit(1);
	}
	else if ((tmp[0] == 65 || tmp[0] == 97) && !tmp[1])
		select_all(d, 1);
	else if ((tmp[0] == 85 || tmp[0] == 117) && !tmp[1])
		select_all(d, 0);
	else if (tmp[0] == 47 && !tmp[1])
		search(d);
	else
		return (in2(d, tmp));
	return (2);
}
