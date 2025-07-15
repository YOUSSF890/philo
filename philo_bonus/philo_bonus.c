/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/15 15:15:39 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void printf_status(char *str, t_data *data) {
    sem_wait(data->print);
    long now = ft_tim_dil() - data->one_tim;  // Recalculate after lock
    printf("%ld %d is %s\n", now, data->id, str);
    if (!strcmp(str, "eating")) 
        data->last_eat = ft_tim_dil();
    sem_post(data->print);
}


void philosopher_action(t_data *data)
{
	if (data->nbr_of_philo == 1)
	{
		printf("%ld %d has taken a fork\n", data->time_to_diel, data->id);
		usleep(data->time_to_diel);
		exit(0);
	}
	int i;
	i = 0;
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

void    monitor_process(t_data *data)
{
	int i;
	
	i = 0;
	while(1)
	{
		sem_wait(data->died);
		printf("died---------------------\n");
		while(i < data->nbr_of_philo)
		{
			kill(data->philo_pids[i], SIGKILL);
			i++;
		}
		exit(0);
		sem_post(data->died);
	}
}

void philo_create(t_data *data, int ac, char *str)
{
	int		i;

	i = 0;
	data->philo_pids = malloc(sizeof(int) * data->nbr_of_philo);
	// data->one_tim = ft_tim_dil();
	while (i < data->nbr_of_philo)
	{
		data->id = i;
		if(ac == 6)
			data->nbr_to_eat = ft_atoi(str);
		else
			data->nbr_to_eat = -1;
		data->last_eat = 0;
		data->one_tim = ft_tim_dil();
		printf("---------1--->%ld\n",ft_tim_dil());
		data->philo_pids[i] = fork();
		printf("------2------>%ld\n",ft_tim_dil());
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
	// int status;
	int	n;

	n = 1;
	data = malloc(sizeof(t_data ) * ft_atoi(av[1]));
	if (!check_argement(av, data, ac))
	{
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_unlink("/died");
		// sem_destroy(data->forks);
		// sem_destroy(data->print);
		// sem_destroy(data->died);
		data->forks = sem_open("/forks", O_CREAT | O_RDWR, 0644, data->nbr_of_philo);
		data->print = sem_open("/print", O_CREAT | O_RDWR, 0644, 1);
		data->died = sem_open("/died", O_CREAT | O_RDWR, 0644, 0);
		philo_create(data , ac , av[5]);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	return (0);
}
