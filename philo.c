/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/05/16 10:50:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo_init(t_philo *philo, char **argv)
{
	philo->philos = ft_atou(argv[1]);
	philo->ttd = ft_atou(argv[2]);
	philo->tte = ft_atou(argv[3]);
	philo->tts = ft_atou(argv[4]);
	if (argv[5])
		philo->rounds = ft_atou(argv[5]);
	else
		philo->rounds = -1;
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n"), 1);
	philo_init(&philo, argv);
}
