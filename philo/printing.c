/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:37:55 by alex              #+#    #+#             */
/*   Updated: 2025/07/10 17:48:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stamp(t_philo *philo, char *str)
{
	printf("%lu %d %s\n", ms_time() - philo->data->start_time, philo->id, str);
}

void	filter_stamp(t_philo *philo, bool flag, unsigned int verb)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (has_simulation_stopped(philo->data) == true && flag == false)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	if (verb == 1)
		stamp(philo, "died");
	else if (verb == 2)
		stamp(philo, "is eating");
	else if (verb == 3)
		stamp(philo, "is sleeping");
	else if (verb == 4)
		stamp(philo, "is thinking");
	else if (verb == 5)
		stamp(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_lock);
}
