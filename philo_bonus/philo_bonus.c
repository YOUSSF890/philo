/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/14 16:04:37 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void printf_status(char *str, t_data *data)
{
	sem_wait(data->print);
	chick_deid(data);
	if(data->some_one_is_deid != 2)
		printf("%ld %d is %s\n",ft_tim_dil() - data->one_tim, data->id, str);
	if(!strcmp(str, "eating"))
		data->last_eat = ft_tim_dil();
	sem_post(data->print);

}

void philosopher_action(t_data *data)
{
	// if (data->nbr_of_philo == 1)
	// {
	// 	printf("%ld %d has taken a fork\n", data->time_to_diel, data->id);
	// 	usleep(data->time_to_diel);
	// 	exit(0);
		
	// }
	
	if(data->id % 2 != 0)
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

void    monitor_process(t_data *data)
{
	int i;
	while(1)
	{
		i = 0;
		while(i < data->nbr_of_philo)
		{
			if(data[i].philo_pids == -1)
			{
				i = 0;
				printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
				while(i < data->nbr_of_philo)
				{
					kill(data[i].philo_pids, SIGKILL);
					i++;
				}
				exit(0);
			}
		}
	}
}

void philo_create(t_data *data, int ac, char *str)
{
	int		i;

	i = 0;
	data->philo_pids = malloc(sizeof(int) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
	{
		data->id = i;
		if(ac == 6)
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
}

int main(int ac, char *av[])
{
	t_data *data;
	int i;
	int status;
	int	n;

	n = 1;
	i = 0;
	data = malloc(sizeof(t_data ) * ft_atoi(av[1]));
	if (!check_argement(av, data, ac))
	{
		// data.forks = malloc(sizeof(sem_t) * data.nbr_of_philo);
		// data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		data->some_one_is_deid = 0;
		data->one_tim = ft_tim_dil();
		data->forks = sem_open("/fork", O_CREAT | O_RDWR, 0644, data->nbr_of_philo);
		data->print = sem_open("/print", O_CREAT | O_RDWR, 0644, 1);
		philo_create(data , ac , av[5]);
		i = 0;
		while (n > 0)
		{
			n = waitpid(-1, &status, 0);
		}
	}
	return (0);
}
