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

void	filter_stamp(t_philo *philo, bool flag, char *verb)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (has_simulation_stopped(philo->data) == true && flag == false)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	if (verb == "die")
		stamp(philo, "died");
	else if (verb == "eat")
		stamp(philo, "is eating");
	else if (verb == "sleep")
		stamp(philo, "is sleeping");
	else if (verb == "think")
		stamp(philo, "is thinking");
	else if (verb == "fork")
		stamp(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_lock);
}
