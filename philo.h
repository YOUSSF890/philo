#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data {
	int				nbr_of_philo;
	int				time_to_diel;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
}				t_data;

typedef struct s_philo
{
	int		id;
	int		nbr_to_eat;
	// int			some_one_is_deid; // 1
	t_data	*data;
	long	last_eat;

	// __
	// pthread_mutex_t	fork;
	// struct s_philo	*next;
}				t_philo;

void	ft_sleep(int ms);
void	ft_check_argement(char **input, t_data *data);
int	ft_atoi(const char *str);

#endif