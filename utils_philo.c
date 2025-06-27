/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:02:00 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/23 15:31:14 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int ms)
{
	usleep(ms);
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

void ft_check_argement(char **input, t_data *data)
{
    int i;
    int j;

    j = 1;
    while (input[j])
    {
        i = 0;
        while (input[j][i])
        {
            if (input[j][i] > 57 || input[j][i] < 48)
            {
                printf("eroor parsin\n");
                exit(1);
            }
            i++;
        }
		stor_data_to_philo(j,  input[j], data);
        j++;
    }
}
