/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:05:17 by meharit           #+#    #+#             */
/*   Updated: 2023/03/03 17:11:03 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

unsigned long long	get_time(t_prm philo)
{
	(void) philo;
	struct timeval fn_time;
	unsigned long long				current_time;

	gettimeofday(&fn_time, NULL);
	current_time = (fn_time.tv_sec) + (fn_time.tv_usec / 1000);
//	printf("%llu	%llu\n", current_time, philo.primary);
	return (current_time);
}

void	time_parm(char **argv, t_time *time, int argc, t_prm *philo)
{
	struct timeval fn_time;

	gettimeofday(&fn_time, NULL);
	time->m_eat = 0;
	time->die = ft_atoi(argv[2]);
	time->eat = ft_atoi(argv[3]);
	time->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		time->m_eat = ft_atoi(argv[5]);
	philo->p_list = NULL;
	philo->primary = (fn_time.tv_sec) + (fn_time.tv_usec / 1000);
	// printf("primary time=> %d\n", philo->primary);
	philo->n_philo = ft_atoi(argv[1]);
}

void	work(t_prm *philo)
{
	(void) philo;
	/* int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(philo->fork[i]));
		printf("%ul ms :: philo 1 has taken a fork", get_time());
	}

	printf("correct\n"); */
}

void	create_philos(t_prm *philo)
{
	pthread_t	thread_id[philo->n_philo];
	int			i;
	int			rc;

	i = 1;
	while (i <= philo->n_philo)
	{
		rc = pthread_create(&thread_id[i-1], NULL, (void*)work, philo);
		if(rc == -1)
		{
			perror("pthread");
			exit(1);
		}
		ft_lstadd_back(&(philo->p_list), ft_lstnew(i));
		philo->p_list->thread_id = thread_id[i-1];
		i++;
	}
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (philo->fork == NULL)
		exit(1);
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
		{
			printf("mutex init has failed\n");
			exit (1);
		}
		printf("A fork is in the table\n");
		i++;
	}
}

#include <limits.h>

int main(int argc, char **argv)
{
	t_time	time;
	t_prm	philo;
	//size_t		i = 0;

	if (argc == 5 || argc == 6)
	{
		time_parm(argv, &time, argc, &philo);
		printf("die=>%d eat=>%d sleep=>%d m_eat=>%d\n", time.die, time.eat, time.sleep, time.m_eat);
		create_philos(&philo);
		philo.current_time = get_time(philo);
		make_mutex(&philo);
	
		while (philo.current_time - philo.primary < philo.primary)
		{
			philo.current_time = get_time(philo);
//			printf("TIME => %d\n", philo.current_time - philo.primary);
//			philo.current_time = get_time(philo);
			printf("TIME => %llu \n", philo.current_time - philo.primary);
//			usleep(1/1000000);
		//	i++;
		}

		// while (philo.p_list)
		// {
		// 	printf("%d\n", philo.p_list->n_eat);
		// 	philo.p_list = philo.p_list->next;
		// }
	}
	else
		ft_putstr_fd("Not enough arguments\n", 2);
}
