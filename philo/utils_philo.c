/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:02:00 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 09:11:40 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ckick_malloc(t_philo *philos, t_data *data)
{
	if (!data->forks)
		return (1);
	if (!data->philosophers)
		return (1);
	if (!philos)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	return (result * sign);
}

void	stor_data_to_philo(int j, char *input, t_data *data)
{
	if (j == 1)
		data->nbr_of_philo = ft_atoi(input);
	if (j == 2)
		data->time_to_diel = ft_atoi(input);
	if (j == 3)
		data->time_to_eat = ft_atoi(input);
	if (j == 4)
		data->time_to_sleep = ft_atoi(input);
}

int	ft_check_argement(char **input, t_data *data, int ac)
{
	int	i;
	int	j;

	j = 1;
	if (ac >= 5 && ac <= 6)
	{
		while (input[j])
		{
			i = 0;
			while (input[j][i])
			{
				if (input[j][i] > 57 || input[j][i] < 48)
					return (write(2, "invalid argument\n", 17), 1);
				i++;
			}
			if (ft_atoi(input[j]) == 0)
				return (write(2, "error argument in 0\n", 20), 1);
			stor_data_to_philo(j, input[j], data);
			j++;
		}
		return (0);
	}
	return (write(2, "should be 5 or 6 arguments\n", 27), 1);
}
