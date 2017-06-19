/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:46:45 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_arg	*char_to_lst(char **argv)
{
	t_arg	*arglst;
	t_arg	*argtmp;
	t_arg	*argtmp2;
	int		i;

	if (!(arglst = (t_arg *)ft_memalloc(sizeof(t_arg))))
		return (NULL);
	argtmp = arglst;
	i = 1;
	while (argv[i])
	{
		argtmp->num = i - 1;
		argtmp->color = arg_color(argv[i]);
		argtmp->elem = ft_strndup(argv[i], ft_strlen_chr(argv[i], '='));
		argtmp->is_select = 0;
		if (!(argtmp->next = (t_arg *)ft_memalloc(sizeof(t_arg))))
			return (NULL);;
		argtmp2 = argtmp;
		argtmp = argtmp->next;
		i++;
	}
	free(argtmp);
	argtmp2->next = NULL;
	return (arglst);
}

void	buff_arg(t_arg **ar, char **buff, int curr, int *whcl)
{
	int	j;

	buffcat(buff, tgoto(tgetstr("cm", NULL), (*ar)->pos_y, whcl[6]));
	if ((*ar)->num == curr)
		buffcat(buff, tgetstr("us", NULL));
	if ((*ar)->is_select)
		buffcat(buff, tgetstr("mr", NULL));
	buffcat(buff, (*ar)->color);
	buffcat(buff, (*ar)->elem);
	buffcat(buff, DEFAULT_COL);
	buffcat(buff, tgetstr("me", NULL));
	whcl[6]++;
	if (whcl[6] == whcl[4] || whcl[6] == whcl[1])
		whcl[7]++;
	(*ar) = (*ar)->next;
	if (whcl[6] == whcl[1])
	{
		j = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
		while ((*ar) && j-- > 0)
			(*ar) = (*ar)->next;
	}
	if (whcl[6] == whcl[4] || whcl[6] == whcl[1])
		whcl[6] = 0;
}

void	disp_arg(t_arg *ar, int *whcl, int curr, char **buff)
{
	int		i;
	int		j;
	int		k;

	k = whcl[3] * whcl[1];
	i = 0;
	whcl[6] = 0;
	whcl[7] = 0;
	j = whcl[5];
	while (ar && j-- > 0)
		ar = ar->next;
	buffcat(buff, tgoto(tgetstr("cm", NULL), 0, 0));
	buffcat(buff, tgetstr("cd", NULL));
	while (ar && k-- > 0)
	{
		ar->pos_x = whcl[6];
		ar->pos_y = whcl[7] * whcl[2];
		buff_arg(&ar, buff, curr, whcl);
		i++;
	}
}

int		*get_size(t_data **save_d)
{
	struct winsize	w;
	int				*whcl;

	ioctl(0, TIOCGWINSZ, &w);
	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (NULL);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - 1;
	if (!(*save_d)->nbr_line || !(*save_d)->nbr_col || !(*save_d)->min_line)
	{
		whcl[3] = nbrline((*save_d)->args, whcl[0], &whcl[2]);
		whcl[4] = nbr_col((*save_d)->args, &whcl[3]);
		(*save_d)->max_len = whcl[2];
		(*save_d)->nbr_line = whcl[3];
		(*save_d)->nbr_col = whcl[4];
	}
	else
	{
		whcl[2] = (*save_d)->max_len;
		whcl[3] = (*save_d)->nbr_line;
		whcl[4] = (*save_d)->nbr_col;
	}
	whcl[5] = check_winsize(*save_d, whcl);
	(*save_d)->min_line = whcl[5];
	return (whcl);
}

void	display_args(t_data *d)
{
	t_data			*save_d;
	char			*buff;
	int				*whcl;

	save_d = d;
	if (!save_d || !save_d->args)
		save_d = get_data(NULL);
	if (!save_d || !save_d->args)
		return ;
	if (!(buff = (char *)ft_memalloc(BUFFER_SIZE + 1)))
		return ;
	if (!(whcl = get_size(&d)))
			return ;
	disp_arg(save_d->args, whcl, save_d->num_curr, &buff);
	ft_putstr_fd(buff, tty_fd(0));
	free(buff);
	free(whcl);
	get_data(save_d);
}
