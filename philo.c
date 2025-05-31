/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 20:46:42 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned int	i;
	unsigned long	now;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->count)
		{
			pthread_mutex_lock(&data->sim_lock);
			now = get_time_ms();
			if ((now - data->philo[i].last_meal) > data->ttd)
			{
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->sim_lock);
				pthread_mutex_lock(&data->print_lock);
				printf("%lu %d died\n", now - data->start_time, data->philo[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->sim_lock);
			i++;
			usleep(1000);
		}
	}
}

void	print_log(t_philo *philo, const char *str)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(&data->sim_lock);
		philo->last_meal = get_time_ms();
		print_log(philo, "is eating");
		pthread_mutex_unlock(&data->sim_lock);
		usleep(data->tte * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (data->rounds != -1 && philo->meals_eaten >= (unsigned int)data->rounds)
			break ;
		print_log(philo, "is sleeping");
		usleep(data->tts * 1000);
		print_log(philo, "is  thinking");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_data			data;
	pthread_t		monitor;

	i = -1;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n"), 1);
	data_init(&data, argc, argv);
	data.start_time = get_time_ms();
	while (++i < data.count)
	{
		pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]);
	}
	pthread_create(&monitor, NULL, (void *)monitor, &data);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data.count)
	{
		printf("This is working\n");
		pthread_join(data.philo[i].thread, NULL);
	}
	ft_exit_mutex(&data);
	return (0);
}
