/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:01:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 16:43:08 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_arg	*hand_tab(t_data **d, t_arg *arg, char *line)
{
	int		num;

	num = (*d)->num_curr;
	if (arg)
		arg = arg->next;
	while (arg && ft_strncmp(arg->elem, (line + 1), ft_strlen((line + 1))))
		arg = arg->next;
	if (!arg)
	{
		arg = (*d)->args;
		while (arg && ft_strncmp(arg->elem, (line + 1), ft_strlen((line + 1))))
			arg = arg->next;
	}
	else if (!ft_strncmp(arg->elem, (line + 1), ft_strlen((line + 1))))
		(*d)->num_curr = arg->num;
	display_onearg(*d, num);
	display_onearg(*d, (*d)->num_curr);
	return (arg);
}

static t_arg	*hand_chr(t_data **d, t_arg *arg, char **line, char *tmp)
{
	char	*tmp2;
	int		num;

	if (tmp[0] == 127 && !tmp[1])
		(*line)[ft_strlen(*line) - 1] = 0;
	else if (tmp[0] == 9 && !tmp[1])
		return (hand_tab(d, arg, *line));
	else if (ft_isprint(tmp[0]) && (tmp[0] != 10 || (tmp[0] == 10 && tmp[1])))
	{
		tmp2 = ft_strjoin(*line, tmp);
		free(*line);
		*line = ft_strdup(tmp2);
		free(tmp2);
		num = (*d)->num_curr;
		arg = (*d)->args;
		while (arg && ft_strncmp(arg->elem, (*line + 1),
					ft_strlen((*line + 1))))
			arg = arg->next;
		if (arg && !ft_strncmp(arg->elem, (*line + 1), ft_strlen((*line + 1))))
			(*d)->num_curr = arg->num;
		display_onearg(*d, num);
		display_onearg(*d, (*d)->num_curr);
	}
	return (arg);
}

void			disp_search(char *line)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	ft_putstr_fd(tgetstr("mr", NULL), tty_fd(0));
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, w.ws_col), tty_fd(0));
	ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
	ft_putstr_fd(line, tty_fd(0));
	ft_putstr_fd(tgetstr("me", NULL), tty_fd(0));
}

void			search(t_data **d)
{
	t_arg			*arg;
	char			*tmp;
	int				num_save;

	num_save = (*d)->num_curr;
	(*d)->line = ft_strdup("/");
	if (!(tmp = (char *)ft_memalloc(7)))
		return ;
	arg = (*d)->args;
	while ((tmp[0] != 10 || (tmp[10] == 10 && tmp[1])) && (*d)->line[0]
			&& (tmp[0] != 27 || tmp[1]) && (*d)->args)
	{
		if (is_term(0) < 0)
			display_args(*d);
		disp_search((*d)->line);
		ft_bzero(tmp, 6);
		read(0, tmp, 6);
		if (!gest_searchin(d, (*d)->line, tmp))
			arg = hand_chr(d, arg, &((*d)->line), tmp);
		else if (!arg)
			arg = (*d)->args;
	}
	free(tmp);
	free((*d)->line);
}
