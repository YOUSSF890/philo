/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/11 17:04:41 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(t_philo *p, int time)
{
	long	start;

	start = ft_tim_dil();
	// 1001 - 1000 < 60
	while (ft_tim_dil() - start <= time)
	{
		if (chick_deid(p))
			return (1);
		usleep(100);
	}
	return (0);
}

long ft_tim_dil()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	long ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (ms);
}

void printf_status(char *str, t_philo *p)
{
	sem_wait(&p->data->print);
	if(!chick_deid(p) && p->data->some_one_is_deid != 2)
		printf("%ld %d is %s\n",ft_tim_dil() - p->data->one_tim, p->id, str);
	if(!strcmp(str, "eating"))
		p->last_eat = ft_tim_dil();
	sem_post(&p->data->print);

}

int chick_deid(t_philo *p)
{
	if (ft_tim_dil() - p->last_eat >= p->data->time_to_diel && p->last_eat != 0)
	{
		if (p->data->some_one_is_deid == 0)
			p->data->some_one_is_deid = 1;
		else
			p->data->some_one_is_deid = 2;
	}
	if (p->data->some_one_is_deid != 0)
	{
		if (p->data->some_one_is_deid == 1)
		{
			p->data->some_one_is_deid = 2;
			printf("%ld %d died------------------\n",ft_tim_dil() - p->data->one_tim, p->id);
		}
		return (1);
	}
	return (0);
}

void	*philosopher(void *arg)
{
	t_philo	*p = (t_philo *)arg;
	int left = p->id;
	if (p->data->nbr_of_philo == 1)
	{
		printf("%ld %d has taken a fork %d\n", p->data->time_to_diel, p->id, left);
		usleep(p->data->time_to_diel);
		return (NULL);
		
	}
	int right = (p->id + 1) % p->data->nbr_of_philo;
	// p->one_tim = ft_tim_dil();
	if (p->id % 2 != 0)
		usleep(500);
	while (1)
	{
		if (p->nbr_to_eat == 0)
			break ;
		if (work_fork(p, left, right))
			return (NULL);
		if (work_eat(p, left, right))
		{
			sem_post(&p->data->forks[right]);
			sem_post(&p->data->forks[left]);
			return (NULL);
		}
		if (work_sleep(p))
			return (NULL);
		if (work_thinking(p))
			return (NULL);
		if (p->nbr_to_eat != -1)
			p->nbr_to_eat--;
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data data;
	int i;

	i = 0;
	if(!ft_check_argement(av, &data, ac))
	{
		// pthread_mutex_init(&data.print, NULL);
		data.print = *sem_open("/print_lock", O_CREAT, 0644, 1);
		t_philo	*philos = malloc(sizeof(t_philo) * data.nbr_of_philo);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		data.some_one_is_deid = 0;
		data.one_tim = ft_tim_dil();
		// data.last_eat = 0;
		while (i < data.nbr_of_philo)
		{
			data.forks[i] = *sem_open("/print_lock", O_CREAT, 0644, 1);
			// pthread_mutex_init(&data.forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < data.nbr_of_philo)
		{
			philos[i].id = i;
			if(ac == 6)
				philos[i].nbr_to_eat = ft_atoi(av[5]);
			else
				philos[i].nbr_to_eat = -1;
			philos[i].data = &data;
			philos[i].last_eat = 0;
			// philos[i].one_tim = ft_tim_dil();
			pthread_create(&data.philosophers[i], NULL, philosopher, &philos[i]);
			i++;
		}
		i = 0;
		while (i < data.nbr_of_philo)
		{
			pthread_join(data.philosophers[i], NULL);
			i++;
		}
		free(data.forks);
		free(data.philosophers);
	}
	return (0);
}
