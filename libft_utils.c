/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:49 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:49 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*f_substr(char *s, long start, long len, short tbf)
{
	char	*res;
	int		i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	if (tbf)
		free(s);
	return (res);
}

char	*ft_strdup(char *s)
{
	char	*d;
	int		i;

	if (!s)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!d)
		return (NULL);
	i = -1;
	while (s[++i])
		d[i] = s[i];
	d[i] = 0;
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		l1;
	int		l2;
	int		i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *) malloc((l1 + l2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		str[i + l1] = s2[i];
		i++;
	}
	str[l1 + l2] = '\0';
	return (str);
}

void	ft_lst_clear(t_flag *f)
{
	t_flag	*tmp;

	while (f)
	{
		if (f->arg)
			free(f->arg);
		tmp = f;
		f = f->next;
		free(tmp);
	}
}
