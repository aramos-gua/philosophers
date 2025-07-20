/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:24:21 by aramos            #+#    #+#             */
/*   Updated: 2025/07/20 12:25:31 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	if (data->rounds == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	sim_delay(data->start_time);
	while (true)
	{
		if (hit_end(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static void	*forever_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	filter_stamp(philo, false, 5);
	ft_sleep(philo->data, philo->data->ttd);
	filter_stamp(philo, false, 1);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->rounds == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_delay(philo->data->start_time);
	if (philo->data->ttd == 0)
		return (NULL);
	if (philo->data->count == 1)
		return (forever_alone(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
	while (has_simulation_stopped(philo->data) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}
