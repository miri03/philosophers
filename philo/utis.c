/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 22:34:10 by meharit           #+#    #+#             */
/*   Updated: 2023/03/25 22:34:12 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(char *mess, long long time, int id, t_prm *philo)
{
	pthread_mutex_lock(&philo->print);
	printf(mess, time, id);
	pthread_mutex_unlock(&philo->print);
}

void	check_meals(t_prm *philo)
{
	if (philo->m_eat < INT_MAX)
	{
		while (philo->end)
		{
			if (philo->finished_eating == philo->n_philo)
				philo->end = 0;
		}
	}
}

int	time_parm(char **argv, int argc, t_prm *philo)
{
	philo->p_list = NULL;
	philo->m_eat = INT_MAX;
	philo->end = 1;
	if (!check_is_digit(argv, argc))
		return (0);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		philo->m_eat = ft_atoi(argv[5]);
	philo->n_philo = ft_atoi(argv[1]);
	return (1);
}

void	ft_eat(t_list *philo)
{
	pthread_mutex_lock(&(philo->fork[philo->id - 1]));
	ft_printf("%lld ms		philo %d has taken a fork\n",
		set_time(philo->info), philo->id, philo->info);
	pthread_mutex_lock(&(philo->fork[philo->id % philo->info->n_philo]));
	ft_printf("%lld ms		philo %d has taken a fork\n",
		set_time(philo->info), philo->id, philo->info);
	ft_printf("%lld ms		philo %d is eating\n",
		set_time(philo->info), philo->id, philo->info);
	philo->last_meal = set_time(philo->info);
	philo->n_eat++;
	if (philo->n_eat == philo->info->m_eat)
	{
		pthread_mutex_lock(&philo->info->meal);
		philo->info->finished_eating++;
		pthread_mutex_unlock(&philo->info->meal);
	}
	sleepi(philo->info->eat);
}

void	sleepi(int x)
{
	struct timeval	start;
	struct timeval	end;
	int				time;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&end, NULL);
		time = (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
				+ start.tv_usec / 1000);
		if (x <= time)
			break ;
	}
}
