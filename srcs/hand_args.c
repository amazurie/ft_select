/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 13:23:41 by amazurie         ###   ########.fr       */
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

int		nbrline(t_arg *arg, int w, int *len)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	*len = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->elem) >= *len)
			*len = ft_strlen(tmp->elem) + 1;
		tmp = tmp->next;
		i++;
	}
	if (i == 1)
		return (1);
	if (w)
		return (w / *len - (w % *len == 0));
	return (0);
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

void	disp_arg(t_arg *ar, int *whcl, int curr, char **buff)
{
	int		i;

	i = 0;
	whcl[0] = 0;
	whcl[1] = 0;
	while (ar)
	{
		buffcat(buff, tgoto(tgetstr("cm", NULL), whcl[0] * whcl[2], whcl[1]));
		if (ar->num == curr)
			buffcat(buff, tgetstr("us", NULL));
		if (ar->is_select)
			buffcat(buff, tgetstr("mr", NULL));
		buffcat(buff, ar->elem);
		buffcat(buff, tgetstr("me", NULL));
		whcl[1]++;
		if (whcl[1] == whcl[4])
			whcl[0]++;
		if (whcl[1] == whcl[4])
			whcl[1] = 0;
		ar = ar->next;
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
	whcl = (int *)ft_memalloc(sizeof(int) * 6);
	buffcat(&buff, tgoto(tgetstr("cm", NULL), 0, 0));
	buffcat(&buff, tgetstr("cd", NULL));
	ioctl(0, TIOCGWINSZ, &w);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row;
	whcl[3] = nbrline(save_d->args, whcl[0], &whcl[2]);
	whcl[4] = nbr_col(save_d->args, &whcl[3]);
	if (check_winsize(save_d->args, &buff, whcl))
		disp_arg(save_d->args, whcl, save_d->num_curr, &buff);
	ft_putstr_fd(buff, tty_fd(0));
	free(buff);
	free(whcl);
}
