/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:07:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/14 15:15:52 by amazurie         ###   ########.fr       */
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
	if (w && i * *len > w)
		return (w / *len - (w % *len == 0));
	if (!w)
	{
		*len = 0;
		return (1);
	}
	return (i);
}

int		nbr_col(t_arg *arg, int w, int *nline)
{
	t_arg	*tmp;
	int		nbr;
	int		l;

	nbr = 0;
	tmp = arg;
	while (tmp->next)
	{
		tmp = tmp->next;
		nbr++;
	}
	*nline -= (((nbr + (nbr % *nline)) / *nline) * *nline < nbr);
	return (((nbr + (nbr % *nline)) / *nline)
			+ (((nbr + (nbr % *nline)) / *nline) * *nline < nbr));
}

void		disp_arg(t_arg *ar, int *whcl, int curr, char **buff)
{
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
		if (whcl[1] == whcl[3])
			whcl[0]++;
		if (whcl[1] == whcl[3])
			whcl[1] = 0;
		ar = ar->next;
	}
}

void		display_args(t_data *d)
{
	t_data			*save_d;
	char			*buff;
	int				*whcl;

	save_d = d;
	if (!save_d)
		save_d = get_data(NULL);
	if (!save_d)
		return ;
	buff = (char *)ft_memalloc(BUFFER_SIZE + 1);
	whcl = (int *)ft_memalloc(sizeof(int) * 5);
	buffcat(&buff, tgoto(tgetstr("cm", NULL), 0, 0));
	buffcat(&buff, tgetstr("cd", NULL));
	whcl[0] = tgetnum("co");
	whcl[1] = tgetnum("li");
	whcl[3] = nbrline(save_d->args, whcl[0], &whcl[2]);
	whcl[3] = nbr_col(save_d->args, whcl[0], &whcl[3]);
	disp_arg(save_d->args, whcl, save_d->num_curr, &buff);
	write(tty_fd(), buff, ft_strlen(buff));
	free(buff);
	free(whcl);
}
