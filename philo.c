/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 19:34:28 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Doing something -> %d\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_data			data;

	i = 0;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n"), 1);
	data_init(&data, argv);
	while (i < data.count)
	{
		printf("creating thread [%d]\n", i);
		pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]);
		i++;
	}
	i = 0;
	while (i < data.count)
	{
		printf("creating thread [%d]\n", i);
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	ft_exit_mutex(&data);
}
