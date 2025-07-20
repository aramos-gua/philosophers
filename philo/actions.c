/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:26:11 by aramos            #+#    #+#             */
/*   Updated: 2025/07/20 12:26:37 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_data *data, unsigned long sleep_time)
{
	unsigned long	alarm;

	alarm = ms_time() + sleep_time;
	while (ms_time() < alarm)
	{
		if (has_simulation_stopped(data))
			break ;
		usleep(100);
	}
}

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	filter_stamp(philo, false, 5);
	pthread_mutex_lock(&philo->data->forks[philo->fork[1]]);
	filter_stamp(philo, false, 5);
	filter_stamp(philo, false, 2);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = ms_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_sleep(philo->data, philo->data->tte);
	if (has_simulation_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	filter_stamp(philo, false, 3);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	ft_sleep(philo->data, philo->data->tts);
}

void	think_routine(t_philo *philo, bool silent)
{
	unsigned long	ttt;

	pthread_mutex_lock(&philo->meal_time_lock);
	ttt = (philo->data->ttd - (ms_time() - philo->last_meal)
			- philo->data->tte) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (ttt == 0 && silent == true)
		ttt = 1;
	if (ttt > 200)
		ttt = 0;
	if (ttt > 600)
		ttt = 200;
	if (silent == false)
		filter_stamp(philo, false, 4);
	ft_sleep(philo->data, ttt);
}
