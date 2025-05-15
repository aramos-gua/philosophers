/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:57:01 by alex              #+#    #+#             */
/*   Updated: 2025/05/15 17:23:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "./libft/libft.h"
#include <pthread.h>
#include <limits.h>

typedef struct	s_philo
{
	unsigned int	philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	int				rounds;
}	t_philo;

#endif
