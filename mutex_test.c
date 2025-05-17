/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:15:37 by aramos            #+#    #+#             */
/*   Updated: 2025/05/17 14:16:53 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int				mails = 0;
pthread_mutex_t	mutex;

void	*routine(void)
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(void)
{
	int			i;
	pthread_t	th[4];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("thread %d started\n", i + 1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("thread %d done\n", i + 1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
