/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:07:50 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 20:46:43 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000));
}

void	philo_init(t_data *data)
{
	unsigned int		i;
	t_philo				*philos;

	i = 0;
	philos = malloc(data->count * sizeof(t_philo));
	if (!philos)
		return ;
	data->philo = philos;
	while (i < data->count)
	{
		philos[i].id = 1 + i;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->count];
		i++;
	}
}

void	data_init(t_data *data, char **argv)
{
	unsigned int	i;

	i = 0;
	data->count = ft_atou(argv[1]);
	data->forks = malloc(data->count * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		printf("Error: Malloc Failed\n");
		return ;
	}
	data->ttd = ft_atou(argv[2]);
	data->tte = ft_atou(argv[3]);
	data->tts = ft_atou(argv[4]);
	if (argv[5])
		data->rounds = ft_atou(argv[5]);
	else
		data->rounds = -1;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->sim_lock, NULL);
	while (i < data->count)
		pthread_mutex_init(&data->forks[i++], NULL);
	philo_init(data);
}
