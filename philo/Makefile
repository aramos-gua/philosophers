# Text styles
DEL_LINE =		\033[2K
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m

# Basic bright colors
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m

# Other colors
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

# Compiler information
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g #-fsanitize=thread #-fsanitize=address
# Target names
NAME = philo

# Files
SRC = ./philo.c\
	  ./init.c\
	./libft.c\
	./error_check.c\
	./threads.c\
	./actions.c\
	./exit.c\
	./printing.c

OBJ = $(SRC:.c=.o)

# Create program
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n${GREEN} Created ${NAME} ${DEF_COLOR}\n"

$(LIBFT):
	@make --no-print-directory -C $(LIBFTDIR)

# Compile .c files into .o files
%.o: %.c
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$< ${DEF_COLOR}"
	@$(CC) $(CFLAGS) -c $< -o $@

# Build all
all: $(NAME)

# Remove .o files
clean:
	@rm -f $(OBJ)

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "\n ${GREEN} Cleaned $(NAME) ${DEF_COLOR}"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
