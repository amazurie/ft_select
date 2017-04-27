/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:05:41 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_arg	*char_to_lst(char **argv)
{
	t_arg	*arglst;
	t_arg	*argtmp;
	t_arg	*argtmp2;
	int		i;

	arglst = (t_arg *)ft_memalloc(sizeof(t_arg));
	argtmp = arglst;
	i = 1;
	while (argv[i])
	{
		argtmp->num = i - 1;
		argtmp->color = arg_color(argv[i]);
		argtmp->elem = ft_strndup(argv[i], ft_strlen_chr(argv[i], '='));
		argtmp->is_select = 0;
		argtmp->next = (t_arg *)ft_memalloc(sizeof(t_arg));
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

	buffcat(buff, tgoto(tgetstr("cm", NULL), whcl[7] * whcl[2], whcl[6]));
	if ((*ar)->num == curr)
		buffcat(buff, tgetstr("us", NULL));
	if ((*ar)->is_select)
		buffcat(buff, tgetstr("mr", NULL));
	buffcat(buff, (*ar)->color);
	buffcat(buff, (*ar)->elem);
	buffcat(buff, DEF_COLOR);
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
		buff_arg(&ar, buff, curr, whcl);
		i++;
	}
}

void	display_args(t_data *d)
{
	struct winsize	w;
	t_data			*save_d;
	char			*buff;
	int				*whcl;

	save_d = d;
	if (!save_d)
		save_d = get_data(NULL);
	if (!save_d)
		return ;
	buff = (char *)ft_memalloc(BUFFER_SIZE + 1);
	whcl = (int *)ft_memalloc(sizeof(int) * 9);
	ioctl(0, TIOCGWINSZ, &w);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - 1;
	whcl[3] = nbrline(save_d->args, whcl[0], &whcl[2]);
	whcl[4] = nbr_col(save_d->args, &whcl[3]);
	whcl[5] = check_winsize(save_d, whcl);
	save_d->max_col = whcl[5];
	disp_arg(save_d->args, whcl, save_d->num_curr, &buff);
	ft_putstr_fd(buff, tty_fd(0));
	free(buff);
	free(whcl);
	get_data(save_d);
}
