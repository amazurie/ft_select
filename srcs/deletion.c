#include "ft_select.h"

void	reset_num(t_data **d)
{
	t_arg	*arg;
	int		i;

	if (!(*d)->args)
		return ;
	arg = (*d)->args;
	i = 0;
	while (arg)
	{
		arg->num = i;
		i++;
		arg = arg->next;
	}
	(*d)->ac = i - 1;
}

static void	del_arg(t_data **d, t_arg **arg, t_arg **tmp)
{
	if (!(*tmp))
	{
		(*tmp) = (*arg);
		(*arg) = (*arg)->next;
		(*d)->args = (*arg);
		free((*tmp)->elem);
		free((*tmp));
		(*tmp) = NULL;
	}
	else
	{
		(*tmp)->next = (*arg)->next;
		free((*arg)->elem);
		free((*arg));
		(*arg) = (*tmp)->next;
	}
}

void		do_del(t_data **d)
{
	t_arg	*arg;
	t_arg	*tmp;

	tmp = NULL;
	arg = (*d)->args;
	while (arg)
	{
		if (arg->is_select)
			del_arg(d, &arg, &tmp);
		else
		{
			tmp = arg;
			arg = arg->next;
		}
	}
	reset_num(d);
	(*d)->num_curr = 0;
}

void		del_curr(t_data **d)
{
	t_arg	*tmp;
	t_arg	*tmp2;

	tmp = (*d)->args;
	tmp2 = NULL;
	while (tmp)
	{
		if (tmp->num == (*d)->num_curr)
		{
			del_arg(d, &tmp, &tmp2);
			reset_num(d);
			if ((*d)->num_curr > (*d)->ac)
				(*d)->num_curr = 0;
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void	free_args(t_arg *arg)
{
	t_arg	*tmp;

	while (arg)
	{
		tmp = arg;
		free(tmp->elem);
		arg = arg->next;
		free(tmp);
	}
	arg = NULL;
}
