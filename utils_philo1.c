#include "philo.h"

int	work_fork(t_philo	*p, int left, int right)
{
	pthread_mutex_lock(&p->data->forks[right]);
	pthread_mutex_lock(&p->data->forks[left]);
	if (chick_deid(p))
	{
		pthread_mutex_unlock(&p->data->forks[right]);
		pthread_mutex_unlock(&p->data->forks[left]);
		return (1);
	}
	printf_status("has taken a fork", p);
	printf_status("has taken a fork", p);

	return (0);
}

int	work_eat(t_philo *p, int left, int right)
{
	printf_status("eating", p);
	// p->last_eat = ft_tim_dil();
	if (chick_deid(p))
		return (1);
	if (ft_usleep(p, p->data->time_to_eat))
	{
		pthread_mutex_unlock(&p->data->forks[right]);
		pthread_mutex_unlock(&p->data->forks[left]);
		return (1);
	}
	pthread_mutex_unlock(&p->data->forks[right]);
	pthread_mutex_unlock(&p->data->forks[left]);
	return (0);
}

int	work_sleep(t_philo *p)
{
	if (chick_deid(p))
		return (1);
	printf_status("sleeping", p);
	if (ft_usleep(p, p->data->time_to_sleep))
		return (1);
	return (0);
}


int	work_thinking(t_philo *p)
{
	if (chick_deid(p))
		return (1);
	printf_status("thinking", p);
	return (0);
}