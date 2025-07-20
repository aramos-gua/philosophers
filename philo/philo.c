/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/07/20 12:33:29 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_sim_stop_flag(t_data *data, bool flag)
{
	pthread_mutex_lock(&data->sim_lock);
	data->sim_stop = flag;
	pthread_mutex_unlock(&data->sim_lock);
}

bool	has_simulation_stopped(t_data *data)
{
	bool	answer;

	answer = false;
	pthread_mutex_lock(&data->sim_lock);
	if (data->sim_stop == true)
		answer = true;
	pthread_mutex_unlock(&data->sim_lock);
	return (answer);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_data			data;

	i = -1;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("%s", USAGE), EXIT_FAILURE);
	data_init(&data, argc, argv);
	data.start_time = ms_time() + (data.count * 200);
	while (++i < data.count)
		pthread_create(&data.philo[i].thread, NULL, &routine, &data.philo[i]);
	usleep(100);
	if (data.count > 1)
		pthread_create(&data.monitor, NULL, &monitor, &data);
	i = -1;
	while (++i < data.count)
		pthread_join(data.philo[i].thread, NULL);
	if (data.count > 1)
		pthread_join(data.monitor, NULL);
	ft_exit_mutex(&data);
	return (EXIT_SUCCESS);
}
