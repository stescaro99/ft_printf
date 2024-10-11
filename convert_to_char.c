/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:58:57 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:58:57 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*convert_address(unsigned long long n)
{
	if (n == 0)
		return (ft_strdup("(nil)"));
	return (f_strjoin("0x", ft_utoa_base(n, 16)));
}

static	char	*convert_string(char *s)
{
	if (!s)
		return (ft_strdup("(null)"));
	return (ft_strdup(s));
}

static	char	*convert_char(int n)
{
	char	c;
	char	*res;

	c = (char)n;
	res = malloc(2);
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

static	char	*convert_caps_hex(unsigned int n)
{
	char	*res;
	int		i;

	res = ft_utoa_base(n, 16);
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		if (res[i] >= 'a' && res[i] <= 'f')
			res[i] -= 32;
		i++;
	}
	return (res);
}

char	*convert_to_char(va_list args, char type)
{
	if (type == 'd' || type == 'i')
		return (ft_itoa_base(va_arg(args, int), 10));
	else if (type == 'u')
		return (ft_utoa_base(va_arg(args, unsigned int), 10));
	else if (type == 'x')
		return (ft_utoa_base(va_arg(args, unsigned int), 16));
	else if (type == 'X')
		return (convert_caps_hex(va_arg(args, unsigned int)));
	else if (type == 'c')
		return (convert_char(va_arg(args, int)));
	else if (type == 's')
		return (convert_string(va_arg(args, char *)));
	else if (type == 'p')
		return (convert_address(va_arg(args, unsigned long long)));
	return (NULL);
}
