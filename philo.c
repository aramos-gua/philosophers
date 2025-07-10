/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/07/10 17:49:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  sim_delay(time_t start_time)
{
  while ((time_t)ms_time() < start_time)
    usleep(100) ;
}
//usleep(100);//instead of continue

void	set_sim_stop_flag(t_data *data, bool flag)
{
	pthread_mutex_lock(&data->sim_lock);
	data->sim_stop = flag;
	pthread_mutex_unlock(&data->sim_lock);
}

bool	has_simulation_stopped(t_data *data)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&data->sim_lock);
	if (data->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&data->sim_lock);
	return (r);
}

bool	starved(t_philo *philo)
{
	time_t	time;

	time = ms_time();
	if ((time - philo->last_meal) >= philo->data->ttd)
	{
		pthread_mutex_unlock(&philo->meal_time_lock);
		set_sim_stop_flag(philo->data, true);
		filter_stamp(philo, true, 1);
		return (true);
	}
	return (false);
}

bool	end_condition_reached(t_data *data)
{
	unsigned int	i;
	bool	all_rounds;

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

void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	if (data->rounds == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	sim_delay(data->start_time);
	while (true)
	{
		if (end_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	philo_sleep(t_data *data, unsigned int sleep_time)
{
	unsigned int	wake_up;

	wake_up = ms_time() + sleep_time;
	while (ms_time() < wake_up)
	{
		if (has_simulation_stopped(data))
			break ;
		usleep(100);
	}
}

void  eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	filter_stamp(philo, false, 5);
	pthread_mutex_lock(&philo->data->forks[philo->fork[1]]);
	filter_stamp(philo, false, 5);
	filter_stamp(philo, false, 2);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = ms_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->data, philo->data->tte);
	if (has_simulation_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	filter_stamp(philo, false, 3);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	philo_sleep(philo->data, philo->data->tts);
}

void  think_routine(t_philo *philo, bool silent)
{
  time_t  ttt;

  pthread_mutex_lock(&philo->meal_time_lock);
  ttt = (philo->data->ttd - (ms_time() - philo->last_meal) - philo->data->tte) / 2;
  pthread_mutex_unlock(&philo->meal_time_lock);
  if (ttt < 0)
    ttt = 0;
  if (ttt == 0 && silent == true)
    ttt = 1;
  if (ttt > 600)
    ttt = 200;
  if (silent == false)
		filter_stamp(philo, false, 4);
  philo_sleep(philo->data, ttt);
}

static void	*forever_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	filter_stamp(philo, false, 5);
	philo_sleep(philo->data, philo->data->ttd);
	filter_stamp(philo, false, 1);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->rounds == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->data->start_time;// - (philo->data->count * 2 * 10);
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_delay(philo->data->start_time);
	if (philo->data->ttd == 0)
		return (NULL);
	if (philo->data->count == 1)
		return(forever_alone(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
	while (has_simulation_stopped(philo->data) == false)
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

	i = 0;
	if (argc < 5 || check_args(argc - 1, argv) || argc > 6)
		return (printf("%s", USAGE), EXIT_FAILURE);
	data_init(&data, argc, argv);
	data.start_time = ms_time() + (data.count * 2 * 10);
	while (i < data.count)
	{
		if (pthread_create(&data.philo[i].thread, NULL, &routine, &data.philo[i]) != 0)
			break ;
		i++;
	}
	if (data.count > 1)
		pthread_create(&data.monitor, NULL, &monitor, &data);
	i = 0;
	while (i < data.count)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	if (data.count > 1)
		pthread_join(data.monitor, NULL);
	ft_exit_mutex(&data);
	return (EXIT_SUCCESS);
}
