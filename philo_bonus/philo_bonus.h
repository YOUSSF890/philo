/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:27:33 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/07/15 20:18:07 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	long	nbr_of_philo;
	long	time_to_diel;
	long	time_to_eat;
	long	time_to_sleep;
	long	one_tim;
	long	some_one_is_deid;
	sem_t	*print;
	sem_t	*forks;
	int		*philo_pids;
	long	last_eat;
	int		nbr_to_eat;
	int		id;
	sem_t	*died;
	sem_t	*not_died;
	sem_t	*wait;
}				t_data;

int		ft_atoi(const char *str);
int		check_argement(char **input, t_data *data, int ac);
void	philo_fork(t_data *data);
void	philo_eating(t_data *data);
void	philo_sleeping(t_data *data);
void	philo_thinking(t_data *data);
void	chick_deid(t_data *data);
void	ft_usleep(t_data *data, int time);
long	ft_tim_dil(void);
void	printf_status(char *str, t_data *data);
void	monitor_process(t_data *data);

#endif