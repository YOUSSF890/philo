/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 10:08:50 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_finsh(t_data *data)
{
	while (1)
	{
		data->nbr_of_philo--;
		if (data->nbr_of_philo == 0)
		{
			sem_post(data->died);
			break ;
		}
	}
}

void	philosopher_action(t_data *data)
{
	if (data->nbr_of_philo == 1)
	{
		printf("%ld %d has taken a fork\n",
			ft_tim_dil() - data->one_tim, data->id + 1);
		usleep(data->time_to_diel * 1000);
		printf("%ld %d died\n", ft_tim_dil() - data->one_tim, data->id + 1);
	}
	else
	{
		if (data->id % 2 != 0)
			usleep(500);
		while (1)
		{
			if (data->nbr_to_eat == 0)
				break ;
			philo_fork(data);
			philo_eating(data);
			philo_sleeping(data);
			philo_thinking(data);
			if (data->nbr_to_eat != -1)
				data->nbr_to_eat--;
		}
	}
	check_finsh(data);
}

void	monitor_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		sem_wait(data->died);
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philo)
	{
		kill(data->philo_pids[i], SIGKILL);
		i++;
	}
	exit(0);
	sem_post(data->died);
}

void	philo_create(t_data *data, int ac, char *str)
{
	int	i;

	i = 0;
	data->philo_pids = malloc(sizeof(int) * data->nbr_of_philo);
	data->one_tim = ft_tim_dil();
	while (i < data->nbr_of_philo)
	{
		data->id = i;
		if (ac == 6)
			data->nbr_to_eat = ft_atoi(str);
		else
			data->nbr_to_eat = -1;
		data->last_eat = 0;
		data->philo_pids[i] = fork();
		if (data->philo_pids[i] == 0)
		{
			philosopher_action(data);
			exit(0);
		}
		i++;
	}
	if (fork() == 0)
		monitor_process(data);
	free(data->philo_pids);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac > 1)
	{
		data = malloc(sizeof(t_data) * ft_atoi(av[1]));
		if (!check_argement(av, data, ac))
		{
			sem_unlink("/forks");
			sem_unlink("/print");
			sem_unlink("/died");
			sem_unlink("/printf_died");
			sem_unlink("/not_died");
			// sem_destroy(data->forks);
			// sem_destroy(data->print);
			// sem_destroy(data->died);
			data->forks = sem_open("/forks", O_CREAT | O_RDWR,
					0644, data->nbr_of_philo);
			data->print = sem_open("/print", O_CREAT | O_RDWR, 0644, 1);
			data->died = sem_open("/died", O_CREAT | O_RDWR, 0644, 0);
			data->not_died = sem_open("/not_died", O_CREAT | O_RDWR, 0644, 0);
			philo_create(data, ac, av[5]);
			while (waitpid(-1, NULL, 0) > 0)
				;
		}
		free(data);
	}
	return (0);
}
