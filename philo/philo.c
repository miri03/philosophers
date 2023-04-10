/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:05:17 by meharit           #+#    #+#             */
/*   Updated: 2023/04/09 19:48:55 by meharit          ###   ########.fr       */
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
		ft_eat(philo);
		pthread_mutex_unlock(&(philo->fork[philo->id - 1]));
		pthread_mutex_unlock(&(philo->fork[philo->id % philo->info->n_philo]));
		ft_printf("%lld ms		philo %d is sleeping\n",
			set_time(philo->info), philo->id, philo->info);
		sleepi(philo->info->sleep);
		ft_printf("%lld ms		philo %d is thinking\n",
			set_time(philo->info), philo->id, philo->info);
	}
	return (NULL);
}

int	create_philos(t_prm *philo)
{
	int	i;

	i = 0;
	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);
	if (philo->p_list == NULL)
	{
		printf("failed to allocate for philos\n");
		return (FAIL);
	}
	philo->init = timer();
	while (i < philo->n_philo)
	{
		philo->p_list[i].n_eat = 0;
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
	return (SUCESS);
}

int	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->meal, NULL);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (philo->fork == NULL)
	{
		printf("failed to allocate for philos\n");
		return (FAIL);
	}
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
			printf("mutex init has failed\n");
		i++;
	}
	return (SUCESS);
}

void	is_dead(t_prm *philo)
{
	int	i;

	i = 0;
	while (philo->end)
	{
		if (i == philo->n_philo)
			i = 0;
		if (set_time(philo) - philo->die > philo->p_list[i].last_meal)
		{
			printf("%lld ms		philo %d is dead\n",
				set_time(philo), philo->p_list[i].id);
			philo->end = 0;
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
				if (make_mutex(&philo) == FAIL)
					return (FAIL);
				if (create_philos(&philo) == FAIL)
					return (FAIL);
				check_meals(&philo);
				is_dead(&philo);
				pthread_mutex_lock(&philo.print);
				usleep(500000);
				free_destroy(&philo);
			}
		}
	}
	else
		ft_putstr_fd(RED "Wrong number of arguments\n" RESET, 2);
}
