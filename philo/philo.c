/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:05:17 by meharit           #+#    #+#             */
/*   Updated: 2023/03/23 15:28:37 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(philo->fork[philo->id - 1]));
		ft_printf("%lld ms		philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		pthread_mutex_lock(&(philo->fork[philo->id % philo->info->n_philo]));
		ft_printf("%lld ms		philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		ft_printf("%lld ms		philo %d is eating\n", set_time(philo->info), philo->id, philo->info);
		
		philo->last_meal = set_time(philo->info);
		sleepi(philo->info->eat);
		ft_printf("%lld ms		philo %d finished eating\n", set_time(philo->info), philo->id, philo->info);
		pthread_mutex_unlock(&(philo->fork[philo->id - 1]));
		pthread_mutex_unlock(&(philo->fork[philo->id % philo->info->n_philo]));
		ft_printf("%lld ms		philo %d is sleeping\n", set_time(philo->info), philo->id, philo->info);
		sleepi(philo->info->sleep);
		ft_printf("%lld ms		philo %d is thinking\n", set_time(philo->info), philo->id, philo->info);
	}
	return (NULL);
}

void	create_philos(t_prm *philo)
{
	int	i;

	i = 0;
	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);
	if (philo->p_list == NULL)
		printf("failed to allocet for philos\n");
	philo->init = timer();
	while (i < philo->n_philo)
	{
		philo->p_list[i].last_meal = set_time(philo);
		philo->p_list[i].id = i + 1;
		philo->p_list[i].info = philo;
		philo->p_list[i].fork = philo->fork;
		pthread_create(&(philo->p_list[i].thread_id), NULL, work,
				&philo->p_list[i]);
		pthread_detach(philo->p_list[i].thread_id);
		usleep(100);
		i++;
	}
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->print, NULL);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
			printf("mutex init has failed\n");
		i++;
	}
}

void	is_dead(t_prm *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == philo->n_philo)
			i = 0;
		if (set_time(philo) - philo->die > philo->p_list[i].last_meal)
		{
			printf("%lld ms		philo %d is dead\n", set_time(philo), philo->p_list[i].id);
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prm	philo;
	
	if (argc == 5 || argc == 6)
	{
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				printf("die=>%d eat=>%d sleep=>%d m_eat=>%d\n", philo.die,
						philo.eat, philo.sleep, philo.m_eat);
				make_mutex(&philo);
				create_philos(&philo);
				is_dead(&philo);
				pthread_mutex_lock(&philo.print);
				usleep(1000000);
				free_destroy(&philo);
			}
		}
	}
	else
		ft_putstr_fd(RED "Wrong number of arguments\n" reset, 2);
}
