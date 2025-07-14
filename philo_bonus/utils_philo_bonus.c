/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:02:00 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/14 14:54:34 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(t_data *data, int time)
{
	long	start;
	start = ft_tim_dil();
	// 1001 - 1000 < 60
	while (ft_tim_dil() - start <= time)
	{
		chick_deid(data);
		usleep(100);
	}
}

long ft_tim_dil()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	long ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (ms);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		result;
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
		i++;
	}
	return (result * sign);
}


void stor_data_to_philo(int j, char *input, t_data *data)
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

int check_argement(char **input, t_data *data, int ac)
{
    int i;
    int j;

    j = 1;
	if (ac >= 5 && ac <= 6)
	{
    	while (input[j])
    	{
    	    i = 0;
    	    while (input[j][i])
    	    {
    	        if (input[j][i] > 57 || input[j][i] < 48)
    	            return (printf("eroor parsin\n"), 1);
    	        i++;
    	    }
			if(ft_atoi(input[j]) == 0)
				return (printf("eroor argemint in 0\n"), 1);
			stor_data_to_philo(j,  input[j], data);
    	    j++;
    	}
		return (0);
	}
	return (printf("eroor parsin in argemint\n"), 1);
}
