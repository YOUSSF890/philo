/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:12:34 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 10:03:28 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *p, int time)
{
	long	start;

	start = ft_tim_dil();
	while (ft_tim_dil() - start <= time)
	{
		if (check_died(p))
			return (1);
		usleep(1000);
	}
	return (0);
}

long	ft_tim_dil(void)
{
	long			ms;
	struct timeval	t;

	gettimeofday(&t, NULL);
	ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (ms);
}

void	printf_status(char *str, t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	if (!check_died(p) && p->data->some_one_is_died != 2)
		printf("%ld %d is %s\n",
			ft_tim_dil() - p->data->one_tim, p->id + 1, str);
	if (!strcmp(str, "eating"))
		p->last_eat = ft_tim_dil();
	pthread_mutex_unlock(&p->data->print);
}
