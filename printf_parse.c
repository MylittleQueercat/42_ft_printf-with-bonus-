/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:42:49 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/16 21:59:17 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*parse_wpt(const char *str, t_format *f)
{
	if (ft_isdigit(*str))
	{
		f->width = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
	}
	if (*str == '.')
	{
		f->dot = 1;
		str++;
		f->precis = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
	}
	if (ft_strchr("cspdiuxX%", *str))
		f->type = *str++;
	return (str);
}

const char	*parse_format(const char *str, t_format *f)
{
	while (*str && ft_strchr("-+ 0#", *str))
	{
		if (*str == '-')
			f->left = 1;
		else if (*str == '+')
			f->sign = 1;
		else if (*str == ' ')
			f->space = 1;
		else if (*str == '0')
			f->zero = 1;
		else if (*str == '#')
			f->hash = 1;
		str++;
	}
	str = parse_wpt(str, f);
	return (str);
}
