/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:26 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:26 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*#include "convert_to_char.c"
#include "ft_print_w_flags.c"
#include "ft_itoa_base.c"
#include "handle_space.c"
#include "libft_utils.c"
#include "utils.c"*/

static	char	find_type(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' || s[i] == 's' || s[i] == 'c' || s[i] == 'd'
			|| s[i] == 'i' || s[i] == 'x' || s[i] == 'X' || s[i] == 'p'
			|| s[i] == 'u')
			return (s[i]);
		i++;
	}
	return (0);
}

static	t_flag	*lst_new(char *s, int *index, char type, char *arg)
{
	int		i;
	t_flag	*new;

	i = 0;
	new = allocate_flags(s, &i);
	if (!new)
		return (NULL);
	new->type = type;
	new->arg = ft_strdup(arg);
	new->ch = ' ';
	if (s[0] == ' ' && ++i)
		new->spc = 1;
	else if (s[0] == '.' && ++i)
		new->prc = 1;
	else if (s[0] == '-' && ++i)
		new->min = 1;
	else if (s[0] == '+' && ++i)
		new->pls = 1;
	else if (s[0] == '#' && ++i)
		new->hsh = 1;
	else if (s[0] == '0' && no_other_flags(s) && ++i)
		new->ch = 48;
	new->n = ft_atol(&s[i]);
	(*index) += i + number_len_base(new->n, 10) + count_zeros(&s[i]);
	return (new);
}

static	void	lst_add_front(t_flag **f, t_flag *tba)
{
	t_flag	*tmp;

	tmp = *f;
	tba->next = tmp;
	*f = tba;
}

static	t_flag	*set_flags(char *s, int *index, va_list args)
{
	int		i;
	short	flag;
	t_flag	*f;
	char	type;
	char	*arg;

	i = 0;
	f = NULL;
	flag = 0;
	type = find_type(s);
	arg = convert_to_char(args, type);
	while (s[i] && ((s[i] != 's' && s[i] != 'c' && s[i] != 'd' && s[i] != 'i'
				&& s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 'u'
				&& s[i] != '%') || (!i && !flag)))
	{
		lst_add_front(&f, lst_new(&s[i], &i, type, arg));
		if (++flag && !f)
			return (NULL);
	}
	free(arg);
	(*index) += i + 1;
	return (f);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	t_flag	*flags;
	char	*s;
	int		res;

	s = (char *)str;
	i = 0;
	res = 0;
	va_start(args, str);
	while (res > -1 && s[i])
	{
		if (s[i] != '%')
			res += write(1, &s[i++], 1);
		else
		{
			i++;
			flags = set_flags(&s[i], &i, args);
			if (!flags)
				return (va_end(args), -1);
			res += print_w_flags(flags);
			ft_lst_clear(flags);
		}
	}
	return (va_end(args), res);
}
/*
int main()
{
	printf("\n%d\n", ft_printf(" %-d ", 10));
 	printf("\n%d\n", printf(" %-d ", 10));
 	return (0);
}*/
