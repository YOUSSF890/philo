#include "philo_bonus.h"

void chick_deid(t_data *data)
{
	if (ft_tim_dil() - data->last_eat >= data->time_to_diel && data->last_eat != 0)
	{
		data->philo_pids = -1;
		printf("--------------------------------\n");
		// if (data->some_one_is_deid == 0)
		// 	data->some_one_is_deid = 1;
		// else
		// 	data->some_one_is_deid = 2;
	}
// 	if (data->some_one_is_deid != 0)
// 	{
// 		if (data->some_one_is_deid == 1)
// 		{
// 			data->some_one_is_deid = 2;
// 			printf("%ld %d died-----------\n",ft_tim_dil() - data->one_tim, data->id);
// 		}
// 		sem_post(data->forks);
// 		sem_post(data->forks);
// 		sem_post(data->print);
// 		exit(1);
// 	}
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
	// p->last_eat = ft_tim_dil();
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