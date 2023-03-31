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

void	work(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->died)
	{
		pthread_mutex_lock(&(philo->info->fork[philo->id - 1]));
		ft_printf("%lld ms		philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		pthread_mutex_lock(&(philo->info->fork[philo->id % philo->info->n_philo]));
		ft_printf("%lld ms		philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		ft_printf("%lld ms		philo %d is eating\n", set_time(philo->info), philo->id, philo->info);

		pthread_mutex_lock(&philo->info->death);
		philo->last_meal = set_time(philo->info);
		pthread_mutex_unlock(&philo->info->death);

		sleepi(philo->info->eat);

		ft_printf("%lld ms		philo %d finished eating\n", set_time(philo->info), philo->id, philo->info);
		pthread_mutex_unlock(&(philo->info->fork[philo->id - 1]));
		pthread_mutex_unlock(&(philo->info->fork[philo->id % philo->info->n_philo]));
		ft_printf("%lld ms		philo %d is sleeping\n", set_time(philo->info), philo->id, philo->info);

		sleepi(philo->info->sleep);
		ft_printf("%lld ms		philo %d is thinking\n", set_time(philo->info), philo->id, philo->info);
	}
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
		philo->p_list[i].died = 0;
		philo->p_list[i].last_meal = set_time(philo);
		philo->p_list[i].id = i + 1;
		philo->p_list[i].info = philo;
		pthread_create(&(philo->p_list[i].thread_id), NULL, (void *)work,
				&philo->p_list[i]);
		usleep(100);
		i++;
	}
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->death, NULL);
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
	int	j;

	j = 0;
	i = 0;
	while (1)
	{
		if (i == philo->n_philo)
			i = 0;
		pthread_mutex_lock(&philo->death);

		if (set_time(philo) - philo->die > philo->p_list[i].last_meal)
		{
			pthread_mutex_unlock(&philo->death);

			pthread_mutex_lock(&philo->print);
			printf("%lld ms		philo %d is dead\n", set_time(philo), philo->p_list[i].id);
			while (j < philo->n_philo)
			{
				pthread_mutex_lock(&philo->death);
				philo->p_list[i].died = 1;
				j++;
				pthread_mutex_unlock(&philo->death);
				
			}			
			return ;
		}
		pthread_mutex_unlock(&philo->death);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prm	philo;
	int		i;

	i = 0;
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
		
				while (i < philo.n_philo)
				{
					pthread_detach(philo.p_list[i].thread_id);
					i++;
				}
				is_dead(&philo);
				free_destroy(&philo);
			}
		}
	}
	else
		ft_putstr_fd(RED "Wrong number of arguments\n" reset, 2);
}
