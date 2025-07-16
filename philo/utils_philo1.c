/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:00:16 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 20:35:54 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_fork(t_philo *p, int left, int right)
{
	pthread_mutex_lock(&p->data->forks[right]);
	pthread_mutex_lock(&p->data->forks[left]);
	if (check_died(p))
	{
		pthread_mutex_unlock(&p->data->forks[right]);
		pthread_mutex_unlock(&p->data->forks[left]);
		return (1);
	}
	printf_status("has taken a fork", p);
	printf_status("has taken a fork", p);
	return (0);
}

int	philo_eat(t_philo *p, int left, int right)
{
	printf_status("eating", p);
	if (check_died(p))
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

int	philo_sleep(t_philo *p)
{
	if (check_died(p))
		return (1);
	printf_status("sleeping", p);
	if (ft_usleep(p, p->data->time_to_sleep))
		return (1);
	return (0);
}

int	philo_thinking(t_philo *p)
{
	if (check_died(p))
		return (1);
	printf_status("thinking", p);
	return (0);
}

void	ft_free_destroy(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	free(data->forks);
	free(data->philosophers);
}
