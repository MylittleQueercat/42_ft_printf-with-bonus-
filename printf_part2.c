/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 08:54:37 by hguo              #+#    #+#             */
/*   Updated: 2025/05/16 21:17:27 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(va_list *args, t_format *f, int *count)
{
	char	c;

	c = (char)va_arg(*args, int);
	if (f->width > 1 && !f->left)
		*count += repeat_char(f->width - 1, ' ');
	*count += write(1, &c, 1);
	if (f->width > 1 && f->left)
		*count += repeat_char(f->width - 1, ' ');
}

void	print_s(va_list *args, t_format *f, int *count)
{
	char	*s;
	int		len;
	int		print_len;

	print_len = 0;
	s = va_arg(*args, char *);
	if (!s)
		len = 6;
	else
		len = ft_strlen(s);
	print_len = len;
	if (s && f->dot && f->precis < len)
		print_len = f->precis;
	else if (!s && f->dot && f->precis < 6)
		print_len = 0;
	if (f->width > print_len && !f->left)
		*count += repeat_char(f->width - print_len, ' ');
	if (!s)
		*count += write(1, "(null)", len);
	else if (s)
		*count += write(1, s, print_len);
	if (f->width > print_len && f->left)
		*count += repeat_char(f->width - print_len, ' ');
}

void	print_p(va_list *args, t_format *f, int *count)
{
	void			*ptr;
	int				len;

	ptr = va_arg(*args, void *);
	if (!ptr)
		len = 5;
	else
		len = count_digits((unsigned long)ptr, 16) + 2;
	if (!f->left && f->width > len)
		*count += repeat_char(f->width - len, ' ');
	if (!ptr && !(f->dot && f->precis == 0))
		*count += write(1, "0x0", 3);
	else
	{
		*count += write(1, "0x", 2);
		if (!(ptr == 0 && f->dot && f->precis == 0))
		{
			print_ubase((unsigned long)ptr, "0123456789abcdef", 16);
			*count += count_digits((unsigned long)ptr, 16);
		}
	}
	if (f->width > len && f->left)
		*count += repeat_char(f->width - len, ' ');
}
