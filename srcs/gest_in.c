/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:37:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 12:56:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*static void		reset(t_data **d)
{
	char	*tmp;

	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), tty_fd(0));
	ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
	tmp = (char *)ft_memalloc(7);
	ft_putstr_fd("warning, all change will be lost continue (y/n)", tty_fd(0));
	while ((tmp[0] != 121 || tmp[0] != 89 || tmp[0] != 110
				|| tmp[0] != 78) && !tmp[1])
		read(0, tmp, 6);
	if (tmp[0] == 89 || tmp[0] == 110)
		return ;
	free_args((*d)->args);
//	(*d)->args = char_to_lst((*d)->av);
//	(*d)->ac = (*d)->ac_save;
	(*d)->num_curr = 0;
}*/

static int		in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
	{
		reset_term(*d);
		exit(1);
	}
	else if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if ((tmp[0] == 127 && !tmp[1])
			|| (tmp[0] == 27 && tmp[1] == 91
				&& tmp[2] == 51 && tmp[3] == 126))
		do_del(d);
	else if (tmp[0] == 27 && tmp[1] == 91)
		return (gest_arrow(d, tmp));
	else if ((tmp[0] == 10) && !tmp[1])
	{
		print_args(*d);
		return (0);
	}
	else if ((tmp[0] == 65 || tmp[0] == 97) && !tmp[1])
		select_all(d, 1);
	else if ((tmp[0] == 85 || tmp[0] == 117) && !tmp[1])
		select_all(d, 0);
	else if ((tmp[0] == 68 || tmp[0] == 100) && !tmp[1])
		del_curr(d);
	else
		return (1);
	return (2);
}

void	user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	tmp = (char *)ft_memalloc(7);
	i = 2;
	while (i)
	{
		if (i == 2)
			display_args(*d);
		read(0, tmp, 6);
//		i = 0;
//		while (tmp[i])
//			printf("%i\n", tmp[i++]);
		i = in(d, tmp);
		get_data(*d);
		ft_bzero(tmp, 6);
		if (!(*d)->args)
			i = 0;
	}
}
