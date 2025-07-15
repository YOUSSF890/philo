#include "philo_bonus.h"

void chick_deid(t_data *data) {
    if (ft_tim_dil() - data->last_eat >= data->time_to_diel && data->last_eat != 0) {
        sem_post(data->forks);
        sem_post(data->forks);
        printf_status("died", data);  // Print death message
        sem_post(data->died);        // Notify monitor
        exit(1);                    // Terminate this philosopher
    }
}


void philo_fork(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	chick_deid(data);
	printf_status("has taken a fork", data);
	printf_status("has taken a fork", data);
}


void	philo_eating(t_data *data)
{
	printf_status("eating", data);
	chick_deid(data);
	ft_usleep(data, data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_sleeping(t_data *data)
{
	chick_deid(data);
	printf_status("sleeping", data);
	ft_usleep(data, data->time_to_sleep);
}


void	philo_thinking(t_data *data)
{
	chick_deid(data);
	printf_status("thinking", data);
}