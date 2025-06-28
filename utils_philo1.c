#include "philo.h"

void	work_fork(t_philo	*p, int left, int right)
{
	pthread_mutex_lock(&p->data->forks[right]);
	printf("Philosopher %d took right fork %d\n", p->id, right);
	pthread_mutex_lock(&p->data->forks[left]);
	printf("Philosopher %d took left fork %d\n", p->id, left);
}

void	work_eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	printf("Philosopher %d is eating..\n", p->id);
	p->last_eat = ft_tim_dil();
	ft_usleep(p->data->time_to_eat);
    pthread_mutex_unlock(&p->data->print);
	// printf("+++{%ld}+++++[%ld]++++++++\n", p->last_eat, ft_tim_dil());
	if(ft_tim_dil() - p->last_eat >= p->data->time_to_diel)
	{
		p->some_one_is_deid = 1;
	}
}

void	work_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	printf("Philosopher %d is sleeping..\n", p->id);
	ft_usleep(p->data->time_to_sleep);
    pthread_mutex_unlock(&p->data->print);
}


void	work_thinking(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
    printf("Philosopher %d is thinking..\n", p->id);
    pthread_mutex_unlock(&p->data->print);
}