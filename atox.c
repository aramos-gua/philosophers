/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:11:34 by alex              #+#    #+#             */
/*   Updated: 2025/05/16 11:20:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (*nptr == '-')
			sign *= -1;
		if (*(nptr + 1) >= '0' && *(nptr + 1) <= '9')
		{
			nptr++;
			break ;
		}
		return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
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

unsigned int	ft_atou(const char *str)
{
	unsigned int	num;

	num = 0;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	return (num);
}
