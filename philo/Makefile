CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
HEADER = philo.h

SRC = philo.c utils_philo.c utils_philo1.c utils_philo2.c \

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