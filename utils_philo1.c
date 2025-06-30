#include "philo.h"

int	work_fork(t_philo	*p, int left, int right)
{
	pthread_mutex_lock(&p->data->forks[right]);
	if (p->data->some_one_is_deid != 0)
	{
		if(p->data->some_one_is_deid == 1)
		{
			p->data->some_one_is_deid = 2;
			printf("tim = %ld X = %d died\n", ft_tim_dil(), p->id);
		}
		pthread_mutex_lock(&p->data->forks[left]);
		return (1);
	}
	printf("tim = %ld X = %d has taken a fork %d\n", ft_tim_dil(), p->id, right);
	pthread_mutex_lock(&p->data->forks[left]);
	printf("tim = %ld X = %d has taken a fork %d\n", ft_tim_dil(), p->id, left);
	return (0);
}

int	work_eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	if(ft_tim_dil() - p->last_eat >= p->data->time_to_diel)
		p->data->some_one_is_deid = 1;
	if (p->data->some_one_is_deid != 0)
	{
		if(p->data->some_one_is_deid == 1)
		{
			p->data->some_one_is_deid = 2;
			printf("tim = %ld X = %d died\n", ft_tim_dil(), p->id);
		}
		pthread_mutex_unlock(&p->data->print);
		return (1);
	}
	printf("tim = %ld X = %d is eating\n", ft_tim_dil(), p->id);
	p->last_eat = ft_tim_dil();
	if (ft_usleep(p))
		return (pthread_mutex_unlock(&p->data->print), 1);
    pthread_mutex_unlock(&p->data->print);
	if(ft_tim_dil() - p->last_eat >= p->data->time_to_diel)
		p->data->some_one_is_deid = 1;
	return (0);
}

int	work_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	if (p->data->some_one_is_deid != 0)
	{
		if(p->data->some_one_is_deid == 1)
		{
			p->data->some_one_is_deid = 2;
			printf("tim = %ld X = %d died\n", ft_tim_dil(), p->id);
		}
		pthread_mutex_unlock(&p->data->print);
		return (1);
	}
	printf("tim = %ld X = %d is sleeping\n", ft_tim_dil(), p->id);
	if (ft_usleep(p))
	{
		pthread_mutex_unlock(&p->data->print);
		return (1);
	}
	pthread_mutex_unlock(&p->data->print);
	return (0);
}


void	work_thinking(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
    printf("tim = %ld X = %d is thinking\n", ft_tim_dil(), p->id);
    pthread_mutex_unlock(&p->data->print);
}