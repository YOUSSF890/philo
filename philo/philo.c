/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/14 17:19:12 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chick_deid(t_philo *p)
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
			printf("%ld %d died\n",
				ft_tim_dil() - p->data->one_tim, p->id);
		}
		return (1);
	}
	return (0);
}

void	work_philo(t_philo	*p, int left, int right)
{
	while (1)
	{
		if (p->nbr_to_eat == 0)
			break ;
		if (work_fork(p, left, right))
			break ;
		if (work_eat(p, left, right))
		{
			pthread_mutex_unlock(&p->data->forks[right]);
			pthread_mutex_unlock(&p->data->forks[left]);
			break ;
		}
		if (work_sleep(p))
			break ;
		if (work_thinking(p))
			break ;
		if (p->nbr_to_eat != -1)
			p->nbr_to_eat--;
	}
}

void	*philosopher(void *arg)
{
	t_philo	*p;
	int		left;
	int		right;

	p = (t_philo *)arg;
	left = p->id;
	if (p->data->nbr_of_philo == 1)
	{
		printf("%ld %d has taken a fork %d\n",
			p->data->time_to_diel, p->id, left);
		usleep(p->data->time_to_diel);
		return (NULL);
	}
	right = (p->id + 1) % p->data->nbr_of_philo;
	if (p->id % 2 != 0)
		usleep(500);
	work_philo(p, left, right);
	return (NULL);
}

void	philo_create(t_data *data, int ac, char *av)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
	{
		philos[i].id = i;
		if (ac == 6)
			philos[i].nbr_to_eat = ft_atoi(av);
		else
			philos[i].nbr_to_eat = -1;
		philos[i].data = data;
		philos[i].last_eat = 0;
		pthread_create(&data->philosophers[i], NULL, philosopher, &philos[i]);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_data	data;
	int		i;

	i = 0;
	if (!ft_check_argement(av, &data, ac))
	{
		pthread_mutex_init(&data.print, NULL);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		data.some_one_is_deid = 0;
		data.one_tim = ft_tim_dil();
		while (i < data.nbr_of_philo)
			pthread_mutex_init(&data.forks[i++], NULL);
		philo_create(&data, ac, av[5]);
		i = 0;
		while (i < data.nbr_of_philo)
			pthread_join(data.philosophers[i++], NULL);
		free(data.forks);
		free(data.philosophers);
	}
	return (0);
}
