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

static int	check_args(int options, char **argv)
{
	while (options > 0)
		if (isnt_number(argv[options--]) == 1)
			return (1);
	return (0);
}

void	philo_init(t_philo *philo, char **argv)
{
	philo->philos = ft_atoi(argv[1]);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	if (argv[5])
		philo->rounds = ft_atoi(argv[5]);
	else
		philo->rounds = -1;
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || check_args(argc - 1, argv))
	{
		ft_printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n");
		return (1);
	}
	philo_init(&philo, argv);
	ft_printf("philos: %d\nttd: %d\ntte: %d\ntts: %d\nrounds: %d\n", philo.philos, philo.ttd, philo.tte, philo.tts, philo.rounds);
}
