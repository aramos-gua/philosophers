/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:43:39 by aramos            #+#    #+#             */
/*   Updated: 2025/07/10 17:20:31 by alex             ###   ########.fr       */
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
