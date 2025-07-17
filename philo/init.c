/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:07:50 by aramos            #+#    #+#             */
/*   Updated: 2025/07/17 15:37:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ms_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error/time: Fetch Error\n", 24);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

static void	get_cutlery(t_philo *philo)
{
	philo->fork[0] = philo->id - 1;
	philo->fork[1] = (philo->id) % philo->data->count;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id) % philo->data->count;
		philo->fork[1] = philo->id - 1;
	}
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
		philo[i].meals_eaten = 0;
		philo[i].last_meal = data->start_time;
		pthread_mutex_init(&philo[i].meal_time_lock, NULL);
		get_cutlery(&philo[i]);
		i++;
	}
}

void	data_init(t_data *data, int argc, char **argv)
{
	unsigned int	i;

	i = 0;
	data->count = ft_atou(argv[1]);
	data->ttd = ft_atou(argv[2]);
	data->tte = ft_atou(argv[3]);
	data->tts = ft_atou(argv[4]);
	data->simulation_end = 0;
	if (argc == 6)
		data->rounds = ft_atoi(argv[5]);
	else
		data->rounds = -1;
	philo_init(data);
	data->forks = malloc(data->count * sizeof(pthread_mutex_t));
	if (!data->forks)
		error_message("Error/init: Malloc Failed\n");
	while (i < data->count)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->sim_lock, NULL);
	data->sim_stop = false;
}
