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

static void	del_arg(t_arg *arg, t_arg *tmp)
{
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
		{
			if (!tmp)
			{
				tmp = arg;
				arg = arg->next;
				(*d)->args = arg;
				free(tmp->elem);
				free(tmp);
				tmp = NULL;
			}
			else
			{
				tmp->next = arg->next;
				free(arg->elem);
				free(arg);
				arg = tmp->next;
			}
		}
		else
		{
			tmp = arg;
			arg = arg->next;
		}
	}
	reset_num(d);
	(*d)->num_curr = 0;
}
