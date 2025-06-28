/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/28 16:26:37 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long duration)
{
	long	start;

	start = ft_tim_dil();
	while (ft_tim_dil() - start <= duration)
	{
		usleep(100);
	}
}

long ft_tim_dil()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	long ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return(ms);
}

void	*philosopher(void *arg)
{
	t_philo	*p = (t_philo *)arg;
	int left = p->id;
	int right = (p->id + 1) % p->data->nbr_of_philo;
	if (p->id % 2 != 0)
		ft_usleep(500);
	while (1)
	{
		if(p->nbr_to_eat == 0)
			break ;
		if (p->id % 2 == 0)
			work_fork(p, left, right);
		else
			work_fork(p, left, right);
		work_eat(p);
		pthread_mutex_unlock(&p->data->forks[left]);
		pthread_mutex_unlock(&p->data->forks[right]);
		if (p->some_one_is_deid == 1)
		{
			printf("dil\n");
			return (NULL);
		}
		work_sleep(p);
		work_thinking(p);
		if (p->nbr_to_eat != -1)
			p->nbr_to_eat--;
	}
	return NULL;
}

int	main(int ac, char *av[])
{
	t_data data;
	int i;

	i = 0;
	if(!ft_check_argement(av, &data, ac))
	{
		t_philo	philos[*av[2]];
    	pthread_mutex_init(&data.print, NULL);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		while (i < data.nbr_of_philo)
		{
			pthread_mutex_init(&data.forks[i], NULL);
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
			philos[i].some_one_is_deid = 0;
			philos[i].data = &data;
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
