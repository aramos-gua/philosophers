/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:34 by alex              #+#    #+#             */
/*   Updated: 2025/05/16 11:21:36 by alex             ###   ########.fr       */
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

static int	off_bounds(int i, char *str)
{
	long	num;

	num = ft_atoln(str);
	if (i == 1 && num > 200)
		return (printf("%s", COUNT_MAX), 1);
	else if (i == 2 || i == 3 || i == 4)
	{
		if (num < 60)
			return (printf("%s", CHOKE), 1);
		if (num > 60000)
			return (printf("%s", WAIT_MAX), 1);
	}
	else if (i == 5 && num > 1000)
		return (printf("%s", ROUNDS_MAX), 1);
	if (num < 0)
		return (1);
	return (0);
}

int	check_args(int options, char **argv)
{
	int	i;

	i = 1;
	while (i <= options)
	{
		if (isnt_pos_number(argv[i]) != 0)
		{
			printf("Error: \"%s\" is not a valid positive number\n", argv[i]);
			return (1);
		}
		if (off_bounds(i, argv[i]) != 0)
		{
			printf("Error: %d argument out of bounds\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}
