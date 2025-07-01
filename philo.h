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
	int				some_one_is_deid; // 1
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
}				t_data;

typedef struct s_philo
{
	int		id;
	int		nbr_to_eat;
	t_data	*data;
	long	last_eat;
	long	one_tim;

	// __
	// pthread_mutex_t	fork;
	// struct s_philo	*next;
}				t_philo;

long	ft_tim_dil();
int chick_deid(t_philo *p);
int		ft_usleep(t_philo *p);
int		ft_atoi(const char *str); 
int		ft_check_argement(char **input, t_data *data, int ac);
int	work_fork(t_philo	*p, int left, int right);
void	work_thinking(t_philo *p);
int		work_sleep(t_philo *p);
int		work_eat(t_philo *p, int left, int right);

#endif