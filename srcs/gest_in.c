#include "ft_select.h"

static int		in(t_data **d, char *tmp)
{
	if (tmp[0] == 27 && !tmp[1])
	{
		reset_term(*d);
		exit(1);
	}
	else if (tmp[0] == 32 && !tmp[1])
		do_space(d);
	else if ((tmp[0] == 127 && !tmp[1])
			|| (tmp[0] == 27 && tmp[1] == 91
				&& tmp[2] == 51 && tmp[3] == 126))
		do_del(d);
	else if (tmp[0] == 27 && tmp[1] == 91)
		return (gest_arrow(d, tmp));
	else if ((tmp[0] == 10) && !tmp[1])
	{
		print_args(*d);
		return (0);
	}
	else if ((tmp[0] == 114 || tmp[0] == 82) && !tmp[1])
		;
	else
		return (1);
	return (2);
}

void	user_hand(t_data **d)
{
	char	*tmp;
	int		i;

	ft_putstr_fd(tgetstr("vi", NULL), tty_fd(0));
	tmp = (char *)ft_memalloc(7);
	i = 2;
	while (i)
	{
		if (i == 2)
			display_args(*d);
		read(0, tmp, 6);
		//		i = 0;
		//		while (tmp[i])
		//			printf("%i\n", tmp[i++]);
		i = in(d, tmp);
		get_data(*d);
		ft_bzero(tmp, 6);
		if (!(*d)->args)
			i = 0;
	}
}
