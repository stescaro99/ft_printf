/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_w_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:11 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:11 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*handle_hashtag(t_flag **f, int *ret)
{
	t_flag	*tmp;
	char	*res;

	tmp = *f;
	res = ft_strdup(tmp->arg);
	if (!res)
		return (NULL);
	if (tmp->arg[0] != '0' && tmp->type == 'x')
		res = f_strjoin("0x", res);
	else if (tmp->arg[0] != '0' && tmp->type == 'X')
		res = f_strjoin("0X", res);
	if (!res)
		return (NULL);
	if (tmp->n && tmp->n > ft_strlen(res))
	{
		free(tmp->arg);
		tmp->arg = ft_strdup(res);
		if (!tmp->arg)
			return (NULL);
		free(res);
		tmp->hsh = 0;
		res = handle_space(*f, ret);
	}
	return (res);
}

static	char	*handle_plus(t_flag **f, int *ret)
{
	t_flag	*tmp;
	char	*res;

	tmp = *f;
	if ((tmp->type == 'd' || tmp->type == 'i') && tmp->arg[0] != '-')
		res = ft_strjoin("+", tmp->arg);
	else
		res = ft_strdup(tmp->arg);
	if (!res)
		return (NULL);
	if (tmp->n && tmp->n > ft_strlen(res))
	{
		free(tmp->arg);
		tmp->arg = ft_strdup(res);
		free(res);
		tmp->pls = 0;
		res = handle_space(*f, ret);
	}
	return (res);
}

static	char	*handle_precision(t_flag *tmp, int *ret)
{
	char	*res;
	char	s;

	s = tmp->type;
	if (s == 's' && !ft_strncmp(tmp->arg, "(null)", 6) && tmp->n < 6)
		return (ft_strdup(""));
	if (s == 's' || (!tmp->n && s != 'p' && s != 'c' && tmp->arg[0] == '0'))
		return (f_substr(tmp->arg, 0, tmp->n, 0));
	res = ft_strdup(tmp->arg);
	if (tmp->n && tmp->n > ft_strlen(tmp->arg) - (tmp->arg[0] == '-'
			|| tmp->arg[0] == '+'))
	{
		free(res);
		if (s != 'p' && s != 'c')
			tmp->ch = '0';
		s = tmp->arg[0];
		if ((tmp->type == 'd' || tmp->type == 'i') && (s == 43 || s == 45))
			tmp->arg = f_substr(tmp->arg, 1, ft_strlen(tmp->arg) - 1, 1);
		res = handle_space(tmp, ret);
		if (s == '-')
			res = f_strjoin("-", res);
		if (s == '+')
			res = f_strjoin("+", res);
	}
	return (res);
}

int	print_w_flags(t_flag *f)
{
	char	*res;
	int		ret;

	if (f->type == '%')
		return (write(1, "%", 1));
	res = ft_strdup(f->arg);
	ret = 0;
	while (res && f)
	{
		free(f->arg);
		f->arg = ft_strdup(res);
		free(res);
		if (f->hsh)
			res = handle_hashtag(&f, &ret);
		else if (f->pls)
			res = handle_plus(&f, &ret);
		else if (f->prc)
			res = handle_precision(f, &ret);
		else
			res = handle_space(f, &ret);
		f = f->next;
	}
	ret += write(1, res, ft_strlen(res));
	return (free(res), ret);
}
