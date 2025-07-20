/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:57:01 by alex              #+#    #+#             */
/*   Updated: 2025/07/11 13:35:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define USAGE "Usage: ./philo [Number of philosophers (1-200)]\
 [Time To Die (60-6000)] [Time To Eat (60-6000)] [Time To Sleep (60-6000)]\
 [Number of times they eat (0-1000)]\n"
# define COUNT_MAX "Sorry, we have sits for up to 200 guests || "
# define CHOKE "Sorry, we don't want our gests to rush, they could choke || "
# define WAIT_MAX "Sorry, we have other guests waiting || "
# define ROUNDS_MAX "Sorry, this is not a buffet || "

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	unsigned int	meals_eaten;
	unsigned long	last_meal;
	pthread_t		thread;
	unsigned int	fork[2];
	pthread_mutex_t	meal_time_lock;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	unsigned int	count;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	int				rounds;

	unsigned long	start_time;
	int				simulation_end;
	bool			sim_stop;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
}	t_data;

//philo.c
void			set_sim_stop_flag(t_data *data, bool flag);
bool			has_simulation_stopped(t_data *data);

//threads.c
void			*routine(void *data);
void			*monitor(void *arg);

//actions.c
void			think_routine(t_philo *philo, bool silent);
void			eat_sleep_routine(t_philo *philo);
void			ft_sleep(t_data *data, unsigned long sleep_time);

//error_check.c
int				check_args(int options, char **argv);

//exit.c
bool			hit_end(t_data *data);
bool			starved(t_philo *philo);
int				error_message(char *str);
void			ft_exit_mutex(t_data *data);

//init.c
void			data_init(t_data *data, int argc, char **argv);
void			philo_init(t_data *data);
void			sim_delay(unsigned long start_time);
size_t			ms_time(void);

//libft.c
int				ft_isdigit(int c);
long			ft_atoln(const char *str);
unsigned long	ft_atou(const char *str);
int				ft_atoi(const char *nptr);

//printing.c
void			filter_stamp(t_philo *philo, bool flag, unsigned int verb);
#endif
