/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:43:39 by aramos            #+#    #+#             */
/*   Updated: 2025/07/20 12:29:59 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->sim_lock);
	pthread_mutex_destroy(&data->philo->meal_time_lock);
	while (i < data->count)
		pthread_mutex_destroy(&data->forks[i++]);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

int	error_message(char *str)
{
	printf("%s", str);
	return (EXIT_FAILURE);
}

bool	starved(t_philo *philo)
{
	unsigned long	time;

	time = ms_time();
	if ((time - philo->last_meal) >= (philo->data->ttd))
	{
		set_sim_stop_flag(philo->data, true);
		filter_stamp(philo, true, 1);
		return (true);
	}
	return (false);
}

bool	hit_end(t_data *data)
{
	unsigned int	i;
	bool			all_rounds;

	all_rounds = true;
	i = 0;
	while (i < data->count)
	{
		pthread_mutex_lock(&data->philo[i].meal_time_lock);
		if (starved(&data->philo[i]))
		{
			pthread_mutex_unlock(&data->philo[i].meal_time_lock);
			return (true);
		}
		if (data->rounds != -1)
			if (data->philo[i].meals_eaten < (unsigned int)data->rounds)
				all_rounds = false;
		pthread_mutex_unlock(&data->philo[i].meal_time_lock);
		i++;
	}
	if (data->rounds != -1 && all_rounds == true)
	{
		set_sim_stop_flag(data, true);
		return (true);
	}
	return (false);
}
