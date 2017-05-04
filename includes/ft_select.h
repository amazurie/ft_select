/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:11:17 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 17:10:06 by amazurie         ###   ########.fr       */
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
# include <sys/stat.h>

# define BUFFER_SIZE 2000
# define DEF_COLOR "\x1b[39m"

typedef struct		s_arg
{
	int				num;
	char			*elem;
	char			*color;
	int				is_select;
	int				pos_x;
	int				pos_y;
	int				line;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_data
{
	struct termios	oldterm;
	struct termios	term;
	int				ac;
	int				min_line;
	int				max_line;
	int				num_curr;
	struct s_arg	*args;
}					t_data;

t_arg				*char_to_lst(char **args);
void				user_hand(t_data **d);
void				display_args(t_data *d);
void				gest_arrow(t_data **d, char *tmp);
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
int					check_winsize(t_data *d, int *whcl);
void				free_args(t_arg *arg);
void				select_all(t_data **d, int etat);
void				del_curr(t_data **d);
char				*arg_color(char *av);
void				search(t_data **d);
void				winsize_changed(int	sig);
int					confirm(char *s);
void				display_onearg(t_data *d, int num);

#endif
