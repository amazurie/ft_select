/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:17 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/18 12:48:14 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H

# define FT_SELECT_H

# include "../libft/includes/libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <term.h>

# define BUFFER_SIZE 2000

typedef struct	s_arg
{
	int				num;
	char			*elem;
	int				is_select;
	struct s_arg	*next;
}				t_arg;

typedef struct		s_data
{
	struct termios	oldterm;
	struct termios	term;
	int				ac;
	int				num_curr;
	struct s_arg	*args;
}					t_data;

t_arg				*char_to_lst(char **args);
void				user_hand(t_data **d);
void				display_args(t_data *d);
int					gest_arrow(t_data **d, char *tmp);
void				do_space(t_data **d);
void				do_del(t_data **d);
int					tty_fd(int i);
void				print_error(char *str);
void				disp_error(char *str);
t_data				*get_data(t_data *d);
void				reset_term(t_data *d);
size_t				print_buff(char **buff);
size_t				buffcat(char **buff, char *s);
void				print_args(t_data *d);
int					nbrline(t_arg *arg, int w, int *len);
int					nbr_col(t_arg *arg, int *nbrline);
int					check_winsize(t_arg *arg, char **buff, int *whcl);
void				free_args(t_arg *arg);
void				select_all(t_data **d, int etat);
void				del_curr(t_data **d);

#endif
