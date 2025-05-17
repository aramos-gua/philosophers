/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:43:39 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 14:53:57 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->count)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}
