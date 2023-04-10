/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:58:14 by meharit           #+#    #+#             */
/*   Updated: 2023/04/10 00:46:22 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	while (1)
	{
		if (set_time(philo->info) - philo->info->die > philo->last_meal)
			exit (philo->id);
		usleep(1000);
	}
	return (NULL);
}

void	ft_eat(t_list *philo)
{
	sem_wait(philo->info->forks);
	ft_printf("%lld ms philo %d has taken a fork\n",
		set_time(philo->info), philo->id, philo->info);
	sem_wait(philo->info->forks);
	ft_printf("%lld ms philo %d has taken a fork\n",
		set_time(philo->info), philo->id, philo->info);
	ft_printf("%lld ms philo %d is eating\n",
		set_time(philo->info), philo->id, philo->info);
	philo->last_meal = set_time(philo->info);
	philo->n_eat++;
	usleep(philo->info->eat * 1000);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	if (philo->n_eat == philo->info->m_eat)
		exit (0);
}

void	work(t_list *philo)
{
	pthread_t	t1;

	pthread_create(&t1, NULL, check_death, philo);
	while (1)
	{
		ft_eat(philo);
		ft_printf("%lld ms philo %d is sleeping\n",
			set_time(philo->info), philo->id, philo->info);
		usleep(philo->info->sleep * 1000);
		ft_printf("%lld ms philo %d is thinking\n",
			set_time(philo->info), philo->id, philo->info);
	}
	pthread_join(t1, NULL);
}

void	make_philos(t_prm *philo)
{
	int	*pid;
	int	i;

	i = 0;
	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);
	if (philo->p_list == NULL)
		exit (1);
	pid = (int *) malloc(sizeof(int) * philo->n_philo);
	if (pid == NULL)
		exit (1);
	philo->init = timer();
	make_semaphores(philo);
	while (i < philo->n_philo)
	{
		init(philo);
		pid[i] = fork();
		if (pid[i] == 0)
		{	
			philo->p_list[i].id = i + 1;
			work(&philo->p_list[i]);
		}
		i++;
	}
	ft_wait(philo, pid);
}

int	main(int argc, char **argv)
{
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		sem_unlink("forks");
		sem_unlink("print");
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				make_philos(&philo);
				sem_close(philo.forks);
				sem_close(philo.forks);
			}
		}
	}
	else
		ft_putstr_fd(RED "Wrong number of arguments\n" RESET, 2);
}
