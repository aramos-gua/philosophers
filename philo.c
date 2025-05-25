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

void	print_log(t_philo *philo, const char *str)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->simulation_end)
	{

	}
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
		if (data->rounds != -1 && philo->meals_eaten >= data->rounds)
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

	i = 0;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n"), 1);
	data.start_time = get_time_ms();
	data_init(&data, argv);
	while (i < data.count)
	{
		printf("creating thread [%d]\n", data.philo[i].id);
		pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]);
		i++;
	}
	i = 0;
	while (i < data.count)
	{
		printf("joining thread [%d]\n", i);
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	ft_exit_mutex(&data);
}
