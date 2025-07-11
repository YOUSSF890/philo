#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h> //
#include <signal.h>

typedef struct s_data {
	long				nbr_of_philo;
	long				time_to_diel;
	long				time_to_eat;
	long				time_to_sleep;
	long	one_tim;
	// long	last_eat;
	long				some_one_is_deid; // 1
	sem_t	print;
	sem_t	*forks;
	pthread_t		*philosophers;
}				t_data;

typedef struct s_philo
{
	int		id;
	int		nbr_to_eat;
	t_data	*data;
	long	last_eat;
	// long	one_tim;
}				t_philo;

long	ft_tim_dil();
int		chick_deid(t_philo *p);
int	ft_usleep(t_philo *p, int time);
int		ft_atoi(const char *str); 
int		ft_check_argement(char **input, t_data *data, int ac);
int		work_fork(t_philo	*p, int left, int right);
int		work_thinking(t_philo *p);
int		work_sleep(t_philo *p);
int		work_eat(t_philo *p, int left, int right);
void printf_status(char *str, t_philo *p);

#endif