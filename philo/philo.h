/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:30 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/16 20:26:54 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	long			nbr_of_philo;
	long			time_to_diel;
	long			time_to_eat;
	long			time_to_sleep;
	long			one_tim;
	long			some_one_is_died;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
}					t_data;

typedef struct s_philo
{
	int		id;
	int		nbr_to_eat;
	t_data	*data;
	long	last_eat;
}			t_philo;

long	ft_tim_dil(void);
int		check_died(t_philo *p);
int		ft_usleep(t_philo *p, int time);
int		ft_atoi(const char *str);
int		ft_check_argement(char **input, t_data *data, int ac);
int		philo_fork(t_philo	*p, int left, int right);
int		philo_thinking(t_philo *p);
int		philo_sleep(t_philo *p);
int		philo_eat(t_philo *p, int left, int right);
void	printf_status(char *str, t_philo *p);
int		ckick_malloc(t_philo *philos, t_data *data);
void	ft_free_destroy(t_data	*data);

#endif