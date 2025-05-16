/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:49:30 by hguo              #+#    #+#             */
/*   Updated: 2025/05/16 21:59:54 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef struct s_format
{
	bool		left;
	bool		sign;
	bool		space;
	bool		hash;
	bool		zero;
	bool		dot;
	int			width;
	int			precis;
	char		type;
}		t_format;

int			ft_printf(const char *format, ...);
void		init_format(t_format *f);
const char	*parse_wpt(const char *str, t_format *f);
const char	*parse_format(const char *str, t_format *f);
void		handle_format(const char **f_ptr, va_list *args, int *count);
void		run_print(const char *f_str, va_list *args, int *count);
int			repeat_char(int count, char c);
int			count_digits(unsigned long num, unsigned int base_len);
long		to_unsigned(long n);
void		print_ubase(unsigned long n, char *base, unsigned int base_len);
void		print_c(va_list *args, t_format *f, int *count);
void		print_s(va_list *args, t_format *f, int *count);
void		print_p(va_list *args, t_format *f, int *count);
void		print_sign(int value, t_format *f, int	*count);
void		print_d(va_list *args, t_format *f, int *count);
void		print_u(va_list *args, t_format *f, int *count);
void		print_x(va_list *args, t_format *f, int *count, char *base);

#endif
