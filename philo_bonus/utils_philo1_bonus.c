#include "philo_bonus.h"

int	work_fork(t_philo	*p, int left, int right)
{
	sem_wait(&p->data->forks[right]);
	sem_wait(&p->data->forks[left]);
	if (chick_deid(p))
	{
		sem_post(&p->data->forks[right]);
		sem_post(&p->data->forks[left]);
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
		sem_post(&p->data->forks[right]);
		sem_post(&p->data->forks[left]);
		return (1);
	}
	sem_post(&p->data->forks[right]);
	sem_post(&p->data->forks[left]);
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