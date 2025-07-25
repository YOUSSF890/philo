/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 20:36:08 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(t_philo *p)
{
	if (ft_tim_dil() - p->last_eat >= p->data->time_to_diel && p->last_eat != 0)
	{
		if (p->data->some_one_is_died == 0)
			p->data->some_one_is_died = 1;
		else
			p->data->some_one_is_died = 2;
	}
	if (p->data->some_one_is_died != 0)
	{
		if (p->data->some_one_is_died == 1)
		{
			p->data->some_one_is_died = 2;
			printf("%ld %d died\n",
				ft_tim_dil() - p->data->one_tim, p->id + 1);
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
		if (philo_fork(p, left, right))
			break ;
		if (philo_eat(p, left, right))
		{
			pthread_mutex_unlock(&p->data->forks[right]);
			pthread_mutex_unlock(&p->data->forks[left]);
			break ;
		}
		if (philo_sleep(p))
			break ;
		if (philo_thinking(p))
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
		printf("%ld %d has taken a fork\n",
			ft_tim_dil() - p->data->one_tim, p->id + 1);
		usleep(p->data->time_to_diel * 1000);
		printf("%ld %d died\n",
			ft_tim_dil() - p->data->one_tim, p->id + 1);
		return (NULL);
	}
	right = (p->id + 1) % p->data->nbr_of_philo;
	if (p->id % 2 != 0)
		usleep(500);
	work_philo(p, left, right);
	return (NULL);
}

void	philo_create(t_data *data, t_philo	*philos, int ac, char *av)
{
	int	i;

	i = 0;
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
	t_philo	*philos;
	t_data	data;
	int		i;

	i = 0;
	if (!ft_check_argement(av, &data, ac))
	{
		pthread_mutex_init(&data.print, NULL);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		philos = malloc(sizeof(t_philo) * data.nbr_of_philo);
		if (ckick_malloc(philos, &data))
			return (1);
		data.some_one_is_died = 0;
		data.one_tim = ft_tim_dil();
		while (i < data.nbr_of_philo)
			pthread_mutex_init(&data.forks[i++], NULL);
		philo_create(&data, philos, ac, av[5]);
		i = 0;
		while (i < data.nbr_of_philo)
			pthread_join(data.philosophers[i++], NULL);
		ft_free_destroy(&data);
		return (free(philos), 0);
	}
	return (0);
}
