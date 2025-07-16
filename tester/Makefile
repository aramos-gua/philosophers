# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 07:04:54 by dantonik          #+#    #+#              #
#    Updated: 2025/07/16 17:28:22 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

re:
	@make fclean -C ../philo
	@make -C ../philo

clean:
	@rm -rf fails
	@rm test

.PHONY:		re clean
