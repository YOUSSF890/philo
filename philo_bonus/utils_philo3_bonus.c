/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:07:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 10:07:54 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_status(char *str, t_data *data)
{
	long	now;

	sem_wait(data->print);
	now = ft_tim_dil() - data->one_tim;
	printf("%ld %d is %s\n", now, data->id + 1, str);
	if (!strcmp(str, "eating"))
		data->last_eat = ft_tim_dil();
	sem_post(data->print);
}
