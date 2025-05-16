/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:57:01 by alex              #+#    #+#             */
/*   Updated: 2025/05/16 11:23:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_philo
{
	unsigned int	philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	int				rounds;
}	t_philo;
// Libft functions
int			ft_isdigit(int c);
long		ft_atoln(const char *str);
unsigned int	ft_atou(const char *str);

// Error handling 
int			check_args(int options, char **argv);
#endif
