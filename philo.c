/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:53 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/27 16:20:46 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_tim_dil()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	long ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return(ms);
}

int cheack_deid_philo(int some_one_is_deid)
{
	if (some_one_is_deid == 0)
		return 0;
	return 1;
}

void	*philosopher(void *arg)
{	
	static int some_one_is_deid;
	t_philo	*p = (t_philo *)arg;
	int left = p->id;
	int right = (p->id + 1) % p->data->nbr_of_philo;
	if (p->id % 2 != 0)
		usleep(500);
	while (!cheack_deid_philo(some_one_is_deid))
	{
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->data->forks[right]);
			printf("Philosopher %d took right fork %d\n", p->id + 1, right);
			pthread_mutex_lock(&p->data->forks[left]);
			printf("Philosopher %d took left fork %d\n", p->id + 1, left);
		}
		else
		{
			pthread_mutex_lock(&p->data->forks[left]);
			printf("Philosopher %d took left fork %d\n", p->id + 1, left);
			pthread_mutex_lock(&p->data->forks[right]);
			printf("Philosopher %d took right fork %d\n", p->id + 1, right);
		}

        pthread_mutex_lock(&p->data->print);
		printf("Philosopher %d is eating...\n", p->id + 1);
        pthread_mutex_unlock(&p->data->print);
		p->last_eat = ft_tim_dil();
		printf("*****************************************************{%ld}\n",ft_tim_dil());
		usleep(p->data->time_to_eat);
		printf("*****************************************************{%ld}\n",ft_tim_dil());
		if (ft_tim_dil() - p->last_eat >= p->data->time_to_eat)
		{
        	pthread_mutex_lock(&p->data->print);
			printf("philo %d  is died{%ld}\n",p->id + 1, ft_tim_dil() - p->last_eat);
        	pthread_mutex_unlock(&p->data->print);
			some_one_is_deid = 1;
			break ;
		}

		pthread_mutex_unlock(&p->data->forks[left]);
		pthread_mutex_unlock(&p->data->forks[right]);

        pthread_mutex_lock(&p->data->print);
		printf("Philosopher %d is sleeping..........................\n", p->id + 1);
        pthread_mutex_unlock(&p->data->print);
		usleep(p->data->time_to_sleep * 100);

        pthread_mutex_lock(&p->data->print);
        printf("Philosopher %d is thinking...\n", p->id + 1);
        pthread_mutex_unlock(&p->data->print);

		printf("-----------{%d}-----------------------------------\n",p->nbr_to_eat);
		p->nbr_to_eat--;
	}
	return NULL;
}

int	main(int ac, char *av[])
{
	t_philo	philos[*av[2]];
	t_data data;
	int i;

	i = 0;
	if(ac >= 5 && ac <= 6)
	{
		ft_check_argement(av, &data);
    	pthread_mutex_init(&data.print, NULL);
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_of_philo);
		data.philosophers = malloc(sizeof(pthread_t) * data.nbr_of_philo);
		while (i < data.nbr_of_philo)
		{
			pthread_mutex_init(&data.forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < data.nbr_of_philo)
		{
			philos[i].id = i;
			// philos[i].nbr_to_eat = ft_atoi(av[5]);
			// philos[i].some_one_is_deid = 0;
			philos[i].data = &data;
			pthread_create(&data.philosophers[i], NULL, philosopher, &philos[i]);
			i++;
		}
		i = 0;
		while (i < data.nbr_of_philo)
		{
			pthread_join(data.philosophers[i], NULL);
			i++;
		}
	}
	else
		printf("eroor parsin in argemint\n");
	free(data.forks);
	free(data.philosophers);
	return (0);
}
