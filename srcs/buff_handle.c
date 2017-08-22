/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:30:06 by amazurie          #+#    #+#             */
/*   Updated: 2017/08/22 15:57:58 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

size_t	print_buff(char **buff)
{
	size_t len;

	len = ft_strlen(*buff);
	ft_putstr_fd(*buff, tty_fd(0));
	ft_bzero(*buff, len);
	return (len);
}

size_t	buffcat(char **buff, char *s)
{
	size_t	len;

	if (!s)
		return (ft_strlen(*buff));
	len = 0;
	if (ft_strlen(*buff) + ft_strlen(s) < BUFFER_SIZE)
		ft_strcat(*buff, s);
	else if (ft_strlen(s) < BUFFER_SIZE)
	{
		len = print_buff(buff);
		ft_strcat(*buff, s);
	}
	else
	{
		len = print_buff(buff) + ft_strlen(s);
		ft_putstr_fd(s, tty_fd(0));
	}
	return (len);
}
