/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:10:15 by meharit           #+#    #+#             */
/*   Updated: 2023/04/08 05:23:51 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(char *mess, long long time, int id, t_prm *philo)
{
	pthread_mutex_lock(&philo->print);
	printf(mess, time, id);
	pthread_mutex_unlock(&philo->print);
}

int	time_parm(char **argv, int argc, t_prm *philo)
{
	philo->p_list = NULL;
	philo->m_eat = -1;
	philo->end = 1;
	if (!check_is_digit(argv, argc))
		return (0);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
		philo->m_eat = ft_atoi(argv[5]);
	if (argc == 5)
		philo->m_eat = INT_MAX;
	philo->n_philo = ft_atoi(argv[1]);
	return (1);
}

int	check_info(t_prm philo)
{
	if (philo.n_philo <= 0 || philo.die <= 0
		|| philo.eat <= 0 || philo.sleep <= 0 || philo.m_eat <= 0)
	{
		printf(RED "invalid parameters\n" RESET);
		return (0);
	}
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
