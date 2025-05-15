/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/05/15 17:24:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isnt_number(char *str)
{
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (1);
	if ((*str == '-' || *str == '+') && !ft_isdigit(str[1]))
		return (1);
	while (*(++str))
	{
		if (!(ft_isdigit(*str)))
			return (1);
	}
	return (0);
}

int	check_args(int options, char **argv)
{
	while (options > 0)
		if (isnt_number(argv[options--]) == 1)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || check_args(argc - 1, argv))
	{
		ft_printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n");
		return (1);
	}

}
