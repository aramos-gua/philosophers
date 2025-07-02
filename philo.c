/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/07/02 15:55:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned int	i;
	unsigned long	now;
	unsigned int	done_eating;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->sim_lock);
		i = 0;
		done_eating = 0;
		now = get_time_ms();
		while (i < data->count)
		{
			if ((now - data->philo[i].last_meal) > data->ttd)
			{
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->sim_lock);
				pthread_mutex_lock(&data->print_lock);
				printf("%lu %d died\n", now - data->start_time, data->philo[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			if (data->rounds != -1 && data->philo[i].meals_eaten >= (unsigned int)data->rounds)
				done_eating++;
			i++;
		}
		if (data->rounds != -1 && done_eating == data->count)
		{
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->sim_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->sim_lock);
		usleep(1000);
	}
}

void	print_log(t_philo *philo, const char *str)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	smart_sleep(unsigned int duration, t_data *data)
{
	unsigned long	start = get_time_ms();
	while (!data->simulation_end && get_time_ms() - start < duration)
		usleep(100);
}

void  sim_delay(time_t start_time)
{
  while (get_time_ms() < start_time)
    continue ;
}

void  eat_sleep_routine(t_philo *philo)
{
  pthread_mutex_lock(&philo->data->right_fork)
  printf("philo grabbed right fork");
  pthread_mutex_lock(&philo->data->left_fork)
  printf("philo grabbed left fork");
  printf("philo is eating");
  pthread_mutex_lock(&philo->meal_time_lock);
  philo->last_meal = get_time_ms();
  pthread_mutex_unlock(&philo->meal_time_lock);
  philo_sleep(philo->data, philo->data->tte);
  if (sim_stopped(philo->data) == false)__
  {
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->meals_eaten += 1;
    pthread_mutex_unlock(&philo->meal_time_lock);
  }
  printf("philo is sleeping");
    pthread_mutex_unlock(&philo->data->left_fork);
    pthread_mutex_unlock(&philo->data->right_fork);
  philo_sleep(philo->data, philo->data->tts);
}

void  think_routine(t_philo *philo, bool silent)
{
  time_t  ttt;

  pthread_mutex_lock(&philo->meal_time_lock);
  ttt = (philo->data->ttd - (get_time_ms() - philo->last_meal) - philo->data->tte) / 2;
  pthread_mutex_unlock(&philo->meal_time_lock);
  if (ttt < 0)
    ttt = 0;
  if (ttt == 0 && silent == true)
    ttt = 1;
  if (ttt > 600)
    ttt = 200;
  if (silen == false)
    printf("philo is thinking");
  philo_sleep(philo->data, ttt);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->rounds == 0)
    return (NULL);
  pthread_mutex_lock(&philo->meal_time_lock);
  philo->last_meal = philo->data->start_time;
  pthread_mutex_unlock(&philo->meal_time_lock);
  sim_delay(philo->data->start_time);
  if (philo->data->ttd == 0)
    return (NULL);
  if (philo->data->count == 1)
    (printf("insert only 1 philo version and return\n"));
  else if (philo->count % 2)
      think_routine(philo, true);
  while (sim_stopped(philo->data) == false)
  {
    eat_sleep_routine(philo);
    think_routine(philo, false);
  }
  return (NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_data			data;

	i = -1;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("Usage: ./philo [No. of philosophers] [TTD] [TTE] [TTS] [No. of rounds]\n"), 1);
	data_init(&data, argc, argv);
  data.start_time = get_time_ms() + (data.count * 2 * 10);
	while (++i < data.count)
	{
		pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]);
	}
	if (data.count > 1)
		pthread_create(&data.monitor, NULL, &monitor, &data);//check monitor thread
	i = -1;
	while (++i < data.count)
	{
		pthread_join(data.philo[i].thread, NULL);
	}
	if (data.count > 1)
		pthread_join(data.monitor, NULL);
	ft_exit_mutex(&data);
	return (0);
}
