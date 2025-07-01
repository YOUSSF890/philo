#include "philo.h"

int	work_fork(t_philo	*p, int left, int right)
{
	// if (chick_deid(p))
	// 	return (1);
	pthread_mutex_lock(&p->data->forks[right]);
	pthread_mutex_lock(&p->data->forks[left]);
	printf("tim = %ld X = %d has taken a fork %d\n", ft_tim_dil() - p->one_tim, p->id, right);
	printf("tim = %ld X = %d has taken a fork %d\n", ft_tim_dil() - p->one_tim, p->id, left);
	return (0);
}

int	work_eat(t_philo *p, int left, int right)
{
	pthread_mutex_lock(&p->data->print);
	printf("tim = %ld X = %d is eating\n", ft_tim_dil() - p->one_tim, p->id);
	if (p->id % 2 == 0)
		p->last_eat = ft_tim_dil();
    pthread_mutex_unlock(&p->data->print);
	if (ft_usleep(p))
		return (pthread_mutex_unlock(&p->data->print), 1);
	pthread_mutex_unlock(&p->data->forks[left]);
	pthread_mutex_unlock(&p->data->forks[right]);
	if (chick_deid(p))
		return (1);
	return (0);
}

int	work_sleep(t_philo *p)
{
	// if (chick_deid(p))
	// 	return (1);
	pthread_mutex_lock(&p->data->print);
	printf("tim = %ld X = %d is sleeping\n", ft_tim_dil() - p->one_tim, p->id);
	pthread_mutex_unlock(&p->data->print);
	if (ft_usleep(p))
	{
		pthread_mutex_unlock(&p->data->print);
		return (1);
	}
	// if (chick_deid(p))
	// 	return (1);
	return (0);
}


void	work_thinking(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
    printf("tim = %ld X = %d is thinking\n", ft_tim_dil() - p->one_tim, p->id);
    pthread_mutex_unlock(&p->data->print);
}