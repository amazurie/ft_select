/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 15:13:14 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/12 15:13:27 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	file_type(mode_t mode)
{
    if (S_ISLNK(mode))
        return ('l');
    if (S_ISDIR(mode))
        return ('d');
    if (S_ISCHR(mode))
        return ('c');
    if (S_ISBLK(mode))
        return ('b');
    if (S_ISFIFO(mode))
        return ('p');
    if (S_ISSOCK(mode))
        return ('s');
    if (mode & S_IXUSR)
        return ('e');
    if (S_ISREG(mode))
        return ('-');
    return ('?');
}

char		*arg_color(char *av)
{
    struct stat	atr;
    
    lstat(av, &atr);
    if (file_type(atr.st_mode) == 'd')
        return ("\x1b[1;36m");
    if (file_type(atr.st_mode) == 'l')
        return ("\x1b[35m");
    if (file_type(atr.st_mode) == 'e')
        return ("\x1b[31m");
    return ("\x1b[39m");
}
