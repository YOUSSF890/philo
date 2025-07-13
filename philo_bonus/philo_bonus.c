/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/13 20:26:20 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int philosopher_action()
{
	printf("philo\n");
	return 0;
}

void philo_create(t_data *data, int ac, char *str)
{
	int i;
	int pid;

	i = 0;
	// t_philo	*philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
	{
		// philos[i].id = i;
		// if(ac == 6)
		// 	philos[i].nbr_to_eat = ft_atoi(str);
		// else
		// 	philos[i].nbr_to_eat = -1;
		// philos[i].data = data;
		// philos[i].last_eat = 0;
		pid = fork();
		if (pid == 0)
		{
			if(philosopher_action())
				exit(0);
		}
		i++;
	}
}

int main(int ac, char *av[])
{
	t_data data;
	int i;
	int status;
	// !check_argement(av, &data, ac)
	if (1)
	{
		// t_philo	*philos = malloc(sizeof(t_philo) * data.nbr_of_philo);
		// data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		// data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		// data.some_one_is_deid = 0;
		// data.one_tim = ft_tim_dil();
		philo_create(&data , ac , av[5]);
		i = 0;
		while (i < data.nbr_of_philo)
		{
			waitpid(-1, &status, 0);
		}
	}
	return (0);
}
