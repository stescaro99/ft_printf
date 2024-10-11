/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:41 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:41 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*set_join(long n, char c)
{
	char	*join;
	long	i;

	if (n < 1)
		return (ft_strdup(""));
	join = malloc(n + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < n)
	{
		join[i] = c;
		i++;
	}
	join[n] = 0;
	return (join);
}

static	char	*handle_spaces_c(char *s, t_flag *f)
{
	long	len_s;
	char	*res;
	char	*join;
	char	*ret;

	res = ft_strdup(s);
	if (!res)
		return (NULL);
	len_s = (long)ft_strlen(res);
	if (!len_s)
		len_s = 1;
	if (len_s > f->n)
		return (res);
	join = set_join(f->n - len_s, f->ch);
	if (!join)
		return (free(res), NULL);
	if (f->min)
		ret = ft_strjoin(res, join);
	else
		ret = ft_strjoin(join, res);
	return (free(res), free(join), ret);
}

static	char	*handle_spaces_d(char *s, t_flag *f)
{
	long	len_s;
	char	*res;
	char	*join;
	char	*ret;
	short	neg;

	if (!f->n && s[0] != '-' && f->ch != '0' && !f->min)
		return (ft_strjoin(" ", s));
	neg = 0;
	if (s[0] == '-' && f->ch == '0')
		neg = 1;
	res = ft_strdup(&s[neg]);
	len_s = (long)ft_strlen(res);
	if (len_s + neg > f->n)
		return (free(res), ft_strdup(s));
	join = set_join(f->n - len_s - neg, f->ch);
	if (!join)
		return (free(res), NULL);
	if (f->min)
		ret = ft_strjoin(res, join);
	else
		ret = ft_strjoin(join, res);
	if (neg)
		ret = f_strjoin("-", ret);
	return (free(res), free(join), ret);
}

static	char	*handle_spaces(char *s, t_flag *f)
{
	long	len_s;
	char	*res;
	char	*join;
	char	*ret;

	res = ft_strdup(s);
	if (!res)
		return (NULL);
	len_s = (long)ft_strlen(res);
	if (!len_s && !f->n)
		len_s = 1;
	if (len_s > f->n)
		return (res);
	join = set_join(f->n - len_s, f->ch);
	if (!join)
		return (free(res), NULL);
	if (f->min)
		ret = ft_strjoin(res, join);
	else
		ret = ft_strjoin(join, res);
	return (free(res), free(join), ret);
}

char	*handle_space(t_flag *f, int *ret)
{
	char	type;
	char	*res;

	type = f->type;
	if (!(f->ch == '0' || f->min || f->spc || f->n || type == 'c'))
		return (ft_strdup(f->arg));
	if (type == 'd' || type == 'i')
		return (handle_spaces_d(f->arg, f));
	if (type == 'c')
	{
		res = handle_spaces_c(f->arg, f);
		if ((ft_strlen(f->arg) == 0 && ft_strlen(res)
				&& f->min) || (!ft_strlen(f->arg) && f->min))
			*ret += write(1, "\0", 1);
		else if ((ft_strlen(f->arg) == 0 && ft_strlen(res))
			|| !ft_strlen(f->arg))
		{
			*ret += write(1, res, ft_strlen(res)) + write(1, "\0", 1);
			return (free(res), ft_strdup(""));
		}
		return (res);
	}
	return (handle_spaces(f->arg, f));
}
