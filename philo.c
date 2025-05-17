/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 15:11:08 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void)
{
	printf("Doing something\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_data			data;

	i = 0;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [Int] [TTD] [TTE] [TTS] [Int]\n"), 1);
	data_init(&data, argv);
	while (i < data.count)
	{
		pthread_create(&data.philo[i].thread, NULL, (void *)routine, &data.philo[i]);
		i++;
	}
	ft_exit_mutex(&data);
}
