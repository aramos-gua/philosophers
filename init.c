/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:07:50 by aramos            #+#    #+#             */
/*   Updated: 2025/07/08 17:47:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ms_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error/time: Fetch Error\n", 24);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void	philo_init(t_data *data)
{
	unsigned int		i;
	t_philo				*philo;

	i = 0;
	philo = malloc(data->count * sizeof(t_philo));
	if (!philo)
	{
		ft_exit_mutex(data);
		error_message("Error/philo: Malloc Failed\n");
	}
	data->philo = philo;
	while (i < data->count)
	{
		philo[i].id = 1 + i;
		philo[i].data = data;
		//philo[i].last_meal = get_time();//already set in main with delay
		philo[i].meals_eaten = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->count];
		pthread_mutex_init(&philo[i].meal_time_lock, NULL);
		i++;
	}
}

void	data_init(t_data *data, int argc, char **argv)
{
	unsigned int	i;

	i = 0;
	data->count = ft_atou(argv[1]);
	data->forks = malloc(data->count * sizeof(pthread_mutex_t));
	if (!data->forks)
		error_message("Error/init: Malloc Failed\n");
	data->ttd = ft_atou(argv[2]);
	data->tte = ft_atou(argv[3]);
	data->tts = ft_atou(argv[4]);
	data->sim_stop = false;
	data->simulation_end = 0;
	if (argc == 6)
		data->rounds = ft_atou(argv[5]);
	else
		data->rounds = -1;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->sim_lock, NULL);
	while (i < data->count)
		pthread_mutex_init(&data->forks[i++], NULL);
	philo_init(data);
}
