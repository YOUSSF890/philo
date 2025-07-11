CC = cc
CFLAGS = -Wall -fsanitize=address -g #-Wextra -Werror
NAME = philo_bonus
HEADER = philo_bonus.h

SRC = philo_bonus.c utils_philo_bonus.c utils_philo1_bonus.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(READ_LINE) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all