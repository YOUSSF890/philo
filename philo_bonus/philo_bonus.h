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
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct s_data {
	long				nbr_of_philo;
	long				time_to_diel;
	long				time_to_eat;
	long				time_to_sleep;
	long	one_tim;
	// long	last_eat;
	long				some_one_is_deid; // 1
	sem_t	*print;
	sem_t	*forks;
	int		*philo_pids;
	pthread_t		*philosophers;
	long	last_eat;
	int		nbr_to_eat;
	int		id;
}				t_data;

// typedef struct s_philo
// {
// 	int		id;
// 	int		nbr_to_eat;
// 	t_data	*data;
// 	long	last_eat;
// 	// long	one_tim;
// }				t_philo;

int		ft_atoi(const char *str); 
int		check_argement(char **input, t_data *data, int ac);

void philo_fork(t_data *data);
void	philo_eating(t_data *data);
void	philo_sleeping(t_data *data);
void	philo_thinking(t_data *data);
void chick_deid(t_data *data);

void	ft_usleep(t_data *data, int time);
long ft_tim_dil();

void printf_status(char *str, t_data *data);
void    monitor_process(t_data *data);

#endif