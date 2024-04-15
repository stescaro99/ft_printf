/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:52:34 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:07 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ull_len_in_base(unsigned long long n, short base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		len++;
		n = n / base;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long long n, short base)
{
	char	*res;
	int		len;
	char	*base_n;

	len = ull_len_in_base(n, base);
	if (len < 1)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	base_n = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (len--)
	{
		res[len] = base_n[n % base];
		n /= base;
	}
	return (res);
}

char	*ft_itoa_base(long long n, short base)
{
	char	*res;

	if (n > -1)
		return (ft_utoa_base(n, base));
	res = f_strjoin("-", ft_utoa_base(-n, base));
	return (res);
}

int	count_zeros(char *s)
{
	int	res;

	if (s[0] < '0' || s[0] > '9')
		return (-1);
	res = 0;
	while (s[res] == '0')
		res++;
	if (s[res] < '0' || s[res] > '9')
		res--;
	return (res);
}

short	no_other_flags(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != 's' && s[i] != 'c' && s[i] != 'd' && s[i] != 'i'
		&& s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 'u'
		&& s[i] != '%')
	{
		if (s[i] == '-' || s[i] == '.' || s[i] == '#'
			|| s[i] == ' ' || s[i] == '+')
			return (0);
		i++;
	}
	return (1);
}
