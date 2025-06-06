/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:57:01 by alex              #+#    #+#             */
/*   Updated: 2025/05/17 20:46:41 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	unsigned int	meals_eaten;
	unsigned long	last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
}	t_data;

// Init
void			data_init(t_data *data, int argc, char **argv);
void			philo_init(t_data *data);
unsigned long	get_time_ms(void);

// Libft functions
int				ft_isdigit(int c);
long			ft_atoln(const char *str);
unsigned int	ft_atou(const char *str);

// Error handling 
int				check_args(int options, char **argv);
void			ft_exit_mutex(t_data *data);
#endif
