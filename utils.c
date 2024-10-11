/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:56 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:56 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (b1[i] != b2[i] || b1[i] == '\0' || b2[i] == '\0')
			return (b1[i] - b2[i]);
		i++;
	}
	return (0);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s2);
	return (str);
}

long	ft_atol(char *s)
{
	long	n;
	int		i;
	int		sign;

	n = 0;
	if (!s || !s[0] || !ft_strncmp(s, "-9223372036854775808", 20))
		return (LONG_MIN);
	sign = 1;
	i = 0;
	if (s[0] == '-')
	{
		i++;
		sign = -1;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		n = 10 * n + s[i] - 48;
		i++;
	}
	return (sign * n);
}

int	number_len_base(long long n, short base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0 && ++len)
		n = -n;
	while (n > 0)
	{
		len++;
		n = n / base;
	}
	return (len);
}

t_flag	*allocate_flags(char *s, int *index)
{
	t_flag	*new;
	int		i;

	new = malloc(sizeof(t_flag));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && s[i + i] && s[i] == s[i + 1] && (s[i] < '0' || s[i] > '9')
		&& s[i] != '.' && s[i] != '%' && s[i] != 's' && s[i] != 'c'
		&& s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X'
		&& s[i] != 'p' && s[i] != 'u')
		i++;
	*index += i;
	new->arg = NULL;
	new->ch = ' ';
	new->hsh = 0;
	new->min = 0;
	new->n = 0;
	new->next = NULL;
	new->pls = 0;
	new->prc = 0;
	new->spc = 0;
	new->type = 0;
	return (new);
}
