/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:25:06 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/15 21:48:58 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	chick_deid(t_data *data)
{
	int i;

	if (ft_tim_dil() - data->last_eat >= data->time_to_diel
		&& data->last_eat != 0)
	{
		sem_post(data->forks);
		sem_post(data->forks);
		sem_wait(data->print);
		printf("%ld %d is died\n", ft_tim_dil() - data->one_tim, data->id);
		i = 0;
		while(i < data->nbr_of_philo)
		{
			sem_post(data->died);
			i++;
		}
		exit(1);
	}
}

void	philo_fork(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	chick_deid(data);
	printf_status("has taken a fork", data);
	printf_status("has taken a fork", data);
}

void	philo_eating(t_data *data)
{
	printf_status("eating", data);
	chick_deid(data);
	ft_usleep(data, data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_sleeping(t_data *data)
{
	chick_deid(data);
	printf_status("sleeping", data);
	ft_usleep(data, data->time_to_sleep);
}

void	philo_thinking(t_data *data)
{
	chick_deid(data);
	printf_status("thinking", data);
}
