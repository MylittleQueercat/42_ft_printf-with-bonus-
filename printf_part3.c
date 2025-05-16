/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:32:50 by hguo              #+#    #+#             */
/*   Updated: 2025/05/16 21:57:42 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(int value, t_format *f, int	*count)
{
	if (value < 0)
		*count += write(1, "-", 1);
	else if (f->sign)
		*count += write(1, "+", 1);
	else if (f->space)
		*count += write(1, " ", 1);
}

void	print_d(va_list *args, t_format *f, int *count)
{
	int	d;
	int	digits;
	int	len;

	d = va_arg(*args, int);
	digits = count_digits(to_unsigned(d), 10);
	len = digits;
	if (f->precis > digits || (f->dot && f->precis == 0 && d == 0))
		len = f->precis;
	if (d < 0 || f->sign || f->space)
		len += 1;
	if (f->width > len && !f->left && !f->zero)
		*count += repeat_char(f->width - len, ' ');
	print_sign(d, f, count);
	if (f->width > len && f->zero && !f->dot && !f->left)
		*count += repeat_char(f->width - len, '0');
	if (f->precis > digits)
		*count += repeat_char(f->precis - digits, '0');
	if (!(d == 0 && f->dot && f->precis == 0))
	{
		print_ubase(to_unsigned(d), "0123456789", 10);
		*count += digits;
	}
	if (f->width > len && f->left)
		*count += repeat_char(f->width - len, ' ');
}

void	print_u(va_list *args, t_format *f, int *count)
{
	unsigned int	u;
	int				numlen;
	int				print_u;

	u = va_arg(*args, unsigned int);
	numlen = count_digits((long)u, 10);
	print_u = numlen;
	if (f->precis > print_u || (!u && f->dot && !f->precis))
		print_u = f->precis;
	if (f->width > print_u && !f->left)
	{
		if (f->zero && !f->dot)
			*count += repeat_char(f->width - print_u, '0');
		else
			*count += repeat_char(f->width - print_u, ' ');
	}
	if (f->precis > numlen)
		*count += repeat_char(f->precis - numlen, '0');
	if (!(u == 0 && f->dot == 1 && f->precis == 0))
	{
		print_ubase(u, "0123456789", 10);
		*count += numlen;
	}
	if (f->left && f->width > print_u)
		*count += repeat_char(f->width - print_u, ' ');
}

void	print_x(va_list *args, t_format *f, int *count, char *base)
{
	unsigned int	x;
	int				len;
	int				digits;

	x = (unsigned int)va_arg(*args, int);
	digits = count_digits(x, 16);
	len = digits;
	if (f->precis > digits || (f->dot && f->precis == 0 && x == 0))
		len = f->precis;
	if (f->hash)
		len += 2;
	if (!f->left && !f->zero && f->width > len)
		*count += repeat_char(f->width - len, ' ');
	*count += write(1, "0x", 2 * (x != 0 && f->hash && f->type == 'x'));
	*count += write(1, "0X", 2 * (x != 0 && f->hash && f->type == 'X'));
	if (f->zero && !f->dot && f->width > len)
		*count += repeat_char(f->width - len, '0');
	if (f->precis > digits)
		*count += repeat_char(f->precis - digits, '0');
	if (!(x == 0 && f->dot && !f->precis))
		print_ubase(x, base, 16);
	if (!(x == 0 && f->dot && !f->precis))
		*count += digits;
	if (f->left && f->width > len)
		*count += repeat_char(f->width - len, ' ');
}
