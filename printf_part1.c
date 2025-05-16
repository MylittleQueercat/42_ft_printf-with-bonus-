/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 08:54:42 by hguo              #+#    #+#             */
/*   Updated: 2025/05/16 21:17:16 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	repeat_char(int count, char c)
{
	int	n;

	n = 0;
	while (n++ < count)
		write(1, &c, 1);
	return (count);
}

int	count_digits(unsigned long num, unsigned int base_len)
{
	int	len;

	len = 1;
	while (num >= base_len)
	{
		num /= base_len;
		len++;
	}
	return (len);
}

long	to_unsigned(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

void	print_ubase(unsigned long n, char *base, unsigned int base_len)
{
	if (n >= base_len)
	{
		print_ubase(n / base_len, base, base_len);
		write(1, &base[n % base_len], 1);
	}
	else
		write(1, &base[n], 1);
}
