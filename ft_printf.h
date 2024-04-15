/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:33 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:33 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_flag
{
	short			prc;
	short			min;
	short			pls;
	short			hsh;
	short			spc;
	char			ch;
	long			n;
	char			type;
	char			*arg;
	struct s_flag	*next;
}				t_flag;

int		ft_printf(const char *str, ...);
long	ft_atol(char *s);
int		number_len_base(long long n, short base);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*f_strjoin(char *s1, char *s2);
char	*f_substr(char *s, long start, long len, short tbf);
char	*ft_strdup(char *s);
char	*ft_itoa_base(long long n, short base);
char	*ft_utoa_base(unsigned long long n, short base);
char	*handle_space(t_flag *f, int *ret);
int		print_w_flags(t_flag *f);
char	*convert_to_char(va_list args, char type);
void	ft_lst_clear(t_flag *f);
t_flag	*allocate_flags(char *s, int *index);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		count_zeros(char *s);
short	no_other_flags(char *s);

#endif