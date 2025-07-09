/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/07/08 17:58:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  sim_delay(time_t start_time)
{
  while ((time_t)ms_time() < start_time)
    usleep(100);
}

void	set_sim_stop_flag(t_data *data, bool state)
{
	pthread_mutex_lock(&data->sim_lock);
	data->sim_stop = state;
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
		set_sim_stop_flag(philo->data, true);
		printf("philo [%d] died\n", philo->id);
		pthread_mutex_unlock(&philo->meal_time_lock);
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
			return (true);
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
	sim_delay(data->start_time);
	if (data->rounds == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	while (true)
	{
		if (end_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
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
	timestamp = (unsigned long)(ms_time() - philo->data->start_time);
	printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	smart_sleep(unsigned int duration, t_data *data)
{
	size_t	start = ms_time();
	while (!data->simulation_end && ms_time() - start < duration)
		usleep(100);
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
	//size_t	now;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lu philo [%d] has taken right fork\n", ms_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lu philo [%d] has taken left fork\n", ms_time() - philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lu philo [%d] has taken left fork\n", ms_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lu philo [%d] has taken right fork\n", ms_time() - philo->data->start_time, philo->id);
	}
	//now = ms_time;
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = ms_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_time_lock);
	printf("%lu philo [%d] is eating\n", ms_time() - philo->data->start_time, philo->id);
	philo_sleep(philo->data, philo->data->tte);
	printf("%lu philo [%d] is sleeping\n", ms_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
    printf("%lu philo [%d] is thinking\n", ms_time() - philo->data->start_time, philo->id);
  philo_sleep(philo->data, ttt);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sim_delay(philo->data->start_time);
	if (philo->data->rounds == 0)
		return (NULL);
	//pthread_mutex_lock(&philo->meal_time_lock);//No need of this block
	//philo->last_meal = philo->data->start_time;//because start_time takes
	//pthread_mutex_unlock(&philo->meal_time_lock);//care of the synch
	if (philo->data->ttd == 0)
		return (NULL);
	if (philo->data->count == 1)
	{
		printf("%lu philo [%d] has taken left fork\n", ms_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->last_meal = ms_time();
		pthread_mutex_unlock(&philo->meal_time_lock);
		usleep(philo->data->ttd * 1000);
		printf("%lu philo[%d] has died\n", ms_time() - philo->data->start_time, philo->id);
		set_sim_stop_flag(philo->data, true);
		return (NULL);
	}
	else if (philo->data->count % 2)
		think_routine(philo, true);
	eat_sleep_routine(philo);
	think_routine(philo, false);
	while (has_simulation_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		if (philo->data->rounds != -1 && philo->meals_eaten >= (unsigned int)philo->data->rounds)
		{
			pthread_mutex_unlock(&philo->meal_time_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_time_lock);
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
		return (printf("%s", USAGE), EXIT_FAILURE);
	data_init(&data, argc, argv);
	data.start_time = ms_time();
	while (++i < data.count)
	{
		data.philo[i].last_meal = data.start_time;
		if (pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]) != 0)
			break ;
	}
	if (data.count > 1)
		pthread_create(&data.monitor, NULL, &monitor, &data);
	i = -1;
	while (++i < data.count)
	{
		pthread_join(data.philo[i].thread, NULL);
	}
	if (data.count > 1)
		pthread_join(data.monitor, NULL);
	ft_exit_mutex(&data);
	return (EXIT_SUCCESS);
}
