/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:01:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:11:57 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_arg	*hand_tab(t_data **d, t_arg *arg, char *line)
{
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
	display_args(*d);
	return (arg);
}

static t_arg	*hand_chr(t_data **d, t_arg *arg, char **line, char *tmp)
{
	char	*tmp2;

	if (tmp[0] == 127 && !tmp[1])
		(*line)[ft_strlen(*line) - 1] = 0;
	else if (tmp[0] == 9 && !tmp[1])
		return (hand_tab(d, arg, *line));
	else if (tmp[0] != 10 || (tmp[0] == 10 && tmp[1]))
	{
		tmp2 = ft_strjoin(*line, tmp);
		free(*line);
		*line = ft_strdup(tmp2);
		free(tmp2);
		arg = (*d)->args;
		while (arg && ft_strncmp(arg->elem, (*line + 1),
					ft_strlen((*line + 1))))
			arg = arg->next;
		if (arg && !ft_strncmp(arg->elem, (*line + 1), ft_strlen((*line + 1))))
			(*d)->num_curr = arg->num;
		display_args(*d);
	}
	return (arg);
}

void			search(t_data **d)
{
	struct winsize	w;
	t_arg			*arg;
	char			*line;
	char			*tmp;
	int				num_save;

	num_save = (*d)->num_curr;
	line = ft_strdup("/");
	tmp = (char *)ft_memalloc(7);
	arg = (*d)->args;
	while ((tmp[0] != 10 || (tmp[10] == 10 && tmp[1])) && line[0])
	{
		ioctl(0, TIOCGWINSZ, &w);
		ft_putstr_fd(tgetstr("mr", NULL), tty_fd(0));
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, w.ws_col), tty_fd(0));
		ft_putstr_fd(tgetstr("cd", NULL), tty_fd(0));
		ft_putstr_fd(line, tty_fd(0));
		ft_putstr_fd(tgetstr("me", NULL), tty_fd(0));
		ft_bzero(tmp, 6);
		read(0, tmp, 6);
		arg = hand_chr(d, arg, &line, tmp);
	}
	free(tmp);
	if (!line[0])
		(*d)->num_curr = num_save;
}
