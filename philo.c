/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/01 23:48:39 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *p)
{
	long	start;

	start = ft_tim_dil();
	while (ft_tim_dil() - start <= p->data->time_to_sleep)
	{
		// if (chick_deid(p))
		// 	return (1);
		usleep(100);
	}
	return (0);
}

// void ft_ft_printf()
// {
// 	if (p->data->some_one_is_deid != 0)
// 	{
// 		if(p->data->some_one_is_deid == 1)
// 		{
// 			p->data->some_one_is_deid = 2;
// 			printf("timestamp_in_ms X died\n");
// 		}
// 		pthread_mutex_unlock(&p->data->print);
// 		return (1);
// 	}
// 	printf("%ld X died\n", ft_tim_dil());
// }

long ft_tim_dil()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	long ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (ms);
}

int chick_deid(t_philo *p)
{
	if (ft_tim_dil() - p->last_eat >= p->data->time_to_diel)
	{
		if (p->data->some_one_is_deid == 0)
		{
			p->data->some_one_is_deid = 1;
		}
		else
		{
			p->data->some_one_is_deid = 2;
		}
	}
	if (p->data->some_one_is_deid != 0)
	{
		if (p->data->some_one_is_deid == 1)
		{
			
			p->data->some_one_is_deid = 2;
			printf("tim = %ld X = %d died\n",p->last_eat, p->id);
		}
		return (1);
	}
	return (0);
}

void	*philosopher(void *arg)
{
	t_philo	*p = (t_philo *)arg;
	int left = p->id;
	int right = (p->id + 1) % p->data->nbr_of_philo;
	p->one_tim = ft_tim_dil();
	if (p->id % 2 != 0)
		usleep(500);
	while (1)
	{
		// if (chick_deid(p))
		// 	return (NULL);
		
		if (p->nbr_to_eat == 0)
			break ;
		if (p->id % 2 == 0)
		{
			if(work_fork(p, left, right))
				return (NULL);
		}
		else
		{
			if(work_fork(p, left, right))
				return (NULL);
		}
		if (work_eat(p, left, right))
		{
			// pthread_mutex_unlock(&p->data->forks[left]);
			// pthread_mutex_unlock(&p->data->forks[right]);
			return (NULL);
		}
		// pthread_mutex_unlock(&p->data->forks[left]);
		// pthread_mutex_unlock(&p->data->forks[right]);
		if (work_sleep(p))
			return (NULL);
		work_thinking(p);
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
		t_philo	philos[*av[2]];
    	pthread_mutex_init(&data.print, NULL);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		data.some_one_is_deid = 0;
		while (i < data.nbr_of_philo)
		{
			pthread_mutex_init(&data.forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < data.nbr_of_philo)
		{
			philos[i].id = i + 1;
			if(ac == 6)
				philos[i].nbr_to_eat = ft_atoi(av[5]);
			else
				philos[i].nbr_to_eat = -1;
			philos[i].data = &data;
			philos[i].data->some_one_is_deid = 0;
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
