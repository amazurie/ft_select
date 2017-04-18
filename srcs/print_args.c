#include "ft_select.h"

void	print_args(t_data *d)
{
	t_arg	*arg;
	char	*buff;

	arg = d->args;
	buff = (char *)ft_memalloc(BUFF_SIZE + 1);
	while (arg)
	{
		if (arg->is_select)
		{
			buffcat(&buff, arg->elem);
			buffcat(&buff, " ");
		}
		arg = arg->next;
	}
	reset_term(get_data(NULL));
	ft_putstr(buff);
	exit(1);
}
