/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:10:56 by aramos            #+#    #+#             */
/*   Updated: 2025/07/03 08:53:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void  sim_delay(time_t start_time)
//{
//  while ((time_t)get_time_ms() < start_time)
//    continue ;
//}
//
//void	set_sim_stop_flag(t_data *data, bool state)
//{
//	pthread_mutex_lock(&data->sim_lock);
//	data->sim_stop = state;
//	pthread_mutex_unlock(&data->sim_lock);
//}
//
//bool	has_simulation_stopped(t_data *data)
//{
//	bool	r;
//
//	r = false;
//	pthread_mutex_lock(&data->sim_lock);
//	if (data->sim_stop == true)
//		r = true;
//	pthread_mutex_unlock(&data->sim_lock);
//	return (r);
//}
//
//bool	kill_philo(t_philo *philo)
//{
//	time_t	time;
//
//	time = get_time_ms();
//	if ((time - philo->last_meal) >= philo->data->ttd)
//	{
//		set_sim_stop_flag(philo->data, true);
//		printf("philo [%d] died\n", philo->id);
//		pthread_mutex_unlock(&philo->meal_time_lock);
//		return (true);
//	}
//	return (false);
//}
//
//bool	end_condition_reached(t_data *data)
//{
//	unsigned int	i;
//	bool	all_ate_enough;
//
//	all_ate_enough = true;
//	i = 0;
//	while (i < data->count)
//	{
//		pthread_mutex_lock(&data->philo[i].meal_time_lock);
//		if (kill_philo(&data->philo[i]))
//			return (true);
//		if (data->rounds != -1)
//			if (data->philo[i].meals_eaten < (unsigned int)data->rounds)
//				all_ate_enough = false;
//		pthread_mutex_unlock(&data->philo[i].meal_time_lock);
//		i++;
//	}
//	if (data->rounds != -1 && all_ate_enough == true)
//	{
//		set_sim_stop_flag(data, true);
//		return (true);
//	}
//	return (false);
//}

void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	if (data->rounds == 0)
		return (NULL);
	//set_sim_stop_flag(data, false);
	//sim_delay(data->start_time);
	//while (true)
	//{
	//	if (end_condition_reached(data) == true)
	//		return (NULL);
	//	usleep(1000);
	//}
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
	timestamp = get_time() - philo->data->start_time;
	printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	smart_sleep(unsigned int duration, t_data *data)
{
	size_t	start = get_time();
	while (!data->simulation_end && get_time() - start < duration)
		usleep(100);
}

void	philo_sleep(t_data *data, unsigned int sleep_time)
{
	unsigned int	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
//		if (has_simulation_stopped(data))
//			break ;
		usleep(100);
		printf("printing something %d\n", data->philo[1].id);
	}
}

void  eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("philo [%d] grabbed right fork\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("philo [%d] grabbed left fork\n", philo->id);
	printf("philo [%d] is eating\n", philo->id);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->data, philo->data->tte);
//	if (has_simulation_stopped(philo->data) == false)
//	{
//		pthread_mutex_lock(&philo->meal_time_lock);
//		philo->meals_eaten += 1;
//		pthread_mutex_unlock(&philo->meal_time_lock);
//	}
	printf("philo [%d]  is sleeping\n", philo->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_sleep(philo->data, philo->data->tts);
}

void  think_routine(t_philo *philo, bool silent)
{
  time_t  ttt;

  pthread_mutex_lock(&philo->meal_time_lock);
  ttt = (philo->data->ttd - (get_time() - philo->last_meal) - philo->data->tte) / 2;
  pthread_mutex_unlock(&philo->meal_time_lock);
  if (ttt < 0)
    ttt = 0;
  if (ttt == 0 && silent == true)
    ttt = 1;
  if (ttt > 600)
    ttt = 200;
  if (silent == false)
    printf("philo [%d] is thinking\n", philo->id);
  philo_sleep(philo->data, ttt);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->rounds == 0)
		return (NULL);
	//pthread_mutex_lock(&philo->meal_time_lock);
	//philo->last_meal = philo->data->start_time;
	//pthread_mutex_unlock(&philo->meal_time_lock);
	//sim_delay(philo->data->start_time);
	if (philo->data->ttd == 0)
		return (NULL);
	if (philo->data->count == 1)
		printf("insert only 1 philo version and return\n");
	//else if (philo->data->count % 2)
	think_routine(philo, true);
	eat_sleep_routine(philo);
	think_routine(philo, false);
	//while (has_simulation_stopped(philo->data) == false)
	//{
	//	eat_sleep_routine(philo);
	//	think_routine(philo, false);
	//}
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
	data.start_time = get_time() + (data.count * 2 * 10);//why, tho?
	while (++i < data.count)
	{
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
