/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 16:39:28 by amazurie         ###   ########.fr       */
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
			return (NULL);
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

	(*ar)->pos_x = whcl[6] + 1;
	(*ar)->pos_y = whcl[7] * whcl[2];
	buffcat(buff, tgoto(tgetstr("cm", NULL), (*ar)->pos_y, whcl[6] + 1));
	(!tgetstr("cm", NULL)) ? buffcat(buff, " ") : 0;
	((*ar)->num == curr) ? buffcat(buff, tgetstr("us", NULL)) : 0;
	((*ar)->is_select) ? buffcat(buff, tgetstr("mr", NULL)) : 0;
	((*ar)->is_select && !tgetstr("cm", NULL)) ? buffcat(buff, ">") : 0;
	buffcat(buff, (*ar)->color);
	buffcat(buff, (*ar)->elem);
	buffcat(buff, DEFAULT_COL);
	buffcat(buff, tgetstr("me", NULL));
	((*ar)->num == curr && !tgetstr("cm", NULL)) ? buffcat(buff, "_") : 0;
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
	(whcl[6] == whcl[4] || whcl[6] == whcl[1]) ? whcl[6] = 0 : 0;
}

void	disp_arg(t_arg *ar, int *whcl, int curr, char **buff)
{
	int		j;
	int		k;

	buffcat(buff, tgetstr("mr", NULL));
	buffcat(buff, tgetstr("md", NULL));
	whcl[6] = whcl[0] - 9;
	while (whcl[6]-- > 0)
	{
		if (whcl[6] == whcl[0] / 2 - 5)
			buffcat(buff, "ft_select");
		buffcat(buff, " ");
	}
	buffcat(buff, tgetstr("me", NULL));
	if (whcl[2] - 1 > whcl[0])
		buffcat(buff, "number of column too low");
	if (whcl[2] - 1 > whcl[0])
		return ;
	k = whcl[3] * whcl[1];
	whcl[6] = 0;
	whcl[7] = 0;
	j = whcl[5];
	while (ar && j-- > 0)
		ar = ar->next;
	while (ar && k-- > 0)
		buff_arg(&ar, buff, curr, whcl);
}

int		*get_size(t_data **save_d)
{
	struct winsize	w;
	int				*whcl;

	ioctl(0, TIOCGWINSZ, &w);
	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (NULL);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - 2;
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
	if (!tgetstr("cm", NULL))
		buffcat(&buff, "\e[1;1H\e[2J");
	buffcat(&buff, tgoto(tgetstr("cm", NULL), 0, 0));
	buffcat(&buff, tgetstr("cd", NULL));
	disp_arg(save_d->args, whcl, save_d->num_curr, &buff);
	if (!tgetstr("cm", NULL))
		buffcat(&buff, "\n");
	ft_putstr_fd(buff, tty_fd(0));
	free(buff);
	free(whcl);
	get_data(save_d);
}
