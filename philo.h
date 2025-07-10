/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:57:01 by alex              #+#    #+#             */
/*   Updated: 2025/07/10 17:49:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define USAGE "Usage: ./philo [Number of philosophers] [Time To Die]\
[Time To Eat] [Time To Sleep] [Number of times they eat]\n"

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	unsigned int	meals_eaten;
	size_t			last_meal;
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
	bool		sim_stop;
	pthread_t       monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
}	t_data;

// Init
void			data_init(t_data *data, int argc, char **argv);
void			philo_init(t_data *data);
size_t			ms_time(void);

// Libft functions
int				ft_isdigit(int c);
long			ft_atoln(const char *str);
unsigned int	ft_atou(const char *str);

// Error handling 
int				check_args(int options, char **argv);
void			ft_exit_mutex(t_data *data);
int				error_message(char *str);
void	filter_stamp(t_philo *philo, bool flag, char *verb);
#endif
