/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:53:10 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 12:33:25 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	char	a;

	a = (char)c;
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			num;
	int			sign;

	sign = 1;
	num = 0;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (!ft_isdigit(*(nptr + 1)))
			return (0);
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	return (num * sign);
}

long	ft_atoln(const char *str)
{
	long			num;
	int				sign;

	sign = 1;
	num = 0;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		if (*(str + 1) && ft_isdigit(*(str + 1)))
		{
			str++;
			break ;
		}
		return (0);
	}
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	return (num * sign);
}

unsigned long	ft_atou(const char *str)
{
	unsigned long	num;

	num = 0;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	return (num);
}
