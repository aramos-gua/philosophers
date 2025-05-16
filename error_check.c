/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:34 by alex              #+#    #+#             */
/*   Updated: 2025/05/16 10:54:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isnt_pos_number(char *str)
{
	if (!(*str == '+' || ft_isdigit(*str)))
		return (1);
	if ((*str == '+') && !ft_isdigit(str[1]))
		return (1);
	while (*(++str))
	{
		if (!(ft_isdigit(*str)))
			return (1);
	}
	return (0);
}

static int	off_bounds(char *str)
{
	long	num;

	num = ft_atoln(str);
	if (num > UINT_MAX)
		return (1);
	if (num < 0)
		return (1);
	return (0);
}

int	check_args(int options, char **argv)
{
	int	i;

	i = 1;
	while (i < options)
	{
		if (isnt_pos_number(argv[i]) !=  0)
		{
			printf("Error: Only possitive numbers as arguments\n");
			return (1);
		}
		if (off_bounds(argv[i]) != 0)
		{
			printf("Error: Number out of bounds\n");
			return (1);
		}
		i++;
	}
	return (0);
}
