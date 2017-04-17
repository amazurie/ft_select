#include "ft_select.h"

static void	left_arrow(t_data **d)
{
	int	w;
	int	c;
	int	l;

	w = tgetnum("co");
	c = nbrline((*d)->args, w, &l);
	l = nbr_col((*d)->args, w, &c);
	if ((*d)->num_curr - l < 0)
	{
		if (c * l - l + (*d)->num_curr - 1 > (*d)->ac)
			(*d)->num_curr = c * l - l * 2 + (*d)->num_curr - 1;
		else
			(*d)->num_curr = c * l - l + (*d)->num_curr - 1;
	}
	else
		(*d)->num_curr -= l;
}

static void	right_arrow(t_data **d)
{
	int	w;
	int	c;
	int	l;

	w = tgetnum("co");
	c = nbrline((*d)->args, w, &l);
	l = nbr_col((*d)->args, w, &c);
	if ((*d)->num_curr + l > (*d)->ac)
	{
		(*d)->num_curr = (*d)->num_curr + l - c * l + 1;
		while ((*d)->num_curr < 0)
			(*d)->num_curr += l;
		if ((*d)->num_curr > (*d)->ac || (*d)->num_curr < 0)
			(*d)->num_curr = (*d)->ac;
	}
	else
		(*d)->num_curr += l;
}

int			gest_arrow(t_data **d, char *tmp)
{
	if (tmp[2] == 65)
		(*d)->num_curr = ((*d)->num_curr == 0) ? (*d)->ac : (*d)->num_curr - 1;
	else if (tmp[2] == 66)
		(*d)->num_curr = ((*d)->num_curr == (*d)->ac) ? (*d)->num_curr = 0 : (*d)->num_curr + 1;
	else if (tmp[2] == 67)
		right_arrow(d);
	else if (tmp[2] == 68)
		left_arrow(d);
	else
		return (1);
	return (2);
}

void	do_space(t_data **d)
{
	t_arg *arg;

	arg = (*d)->args;
	while (arg && arg->num != (*d)->num_curr)
		arg = arg->next;
	if (arg->num == (*d)->num_curr)
	{
		if (arg->is_select)
			arg->is_select = 0;
		else
			arg->is_select = 1;
	}
	right_arrow(d);
}
