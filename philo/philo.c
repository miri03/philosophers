/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:05:17 by meharit           #+#    #+#             */
/*   Updated: 2023/03/20 18:37:48 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

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

	philo->m_eat = 0;
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);

	if (argc == 6)
		time->m_eat = ft_atoi(argv[5]);
	philo->primary = (fn_time.tv_sec) + (fn_time.tv_usec / 1000);
	// printf("primary time=> %d\n", philo->primary);
	philo->n_philo = ft_atoi(argv[1]);
	philo->philo_id = 1;
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (philo->fork == NULL)
		exit(1);
	printf("\n");
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
		{
			printf("mutex init has failed\n");
			exit (1);
		}
		printf("forks ========> %d\n", i+1);
		i++;
	}
	printf("\n");
}

void	work(t_prm *philo)				// problem in forks 
{
	/* if (philo->philo_id % 2 == 0)
		 usleep(1500); */
	printf("%d\n", philo->philo_id);
/*
	// while (1)
	// {
		if (pthread_mutex_lock(&(philo->fork[philo->philo_id - 1])) == 0)
			printf("philo %d has taken the fork %d \n", philo->philo_id, philo->philo_id - 1);
		else
		 printf("------------failed to take a fork\n");

		if (pthread_mutex_lock(&(philo->fork[philo->philo_id])) == 0)
			printf("philo %d has taken the fork %d\n", philo->philo_id, philo->philo_id);
		printf("philo %d is eating\n", philo->philo_id);

		usleep(philo->eat * 1000);
		printf("\nphilo %d finished eating\n", philo->philo_id);

		// printf("\nphilo %d is sleeping\n", philo->philo_id);
		// usleep(philo->sleep * 1000);


		if (pthread_mutex_unlock(&(philo->fork[philo->philo_id - 1])))
				printf("1 unlock failed\n");
		else
			printf("fork %d is in the table\n", philo->philo_id - 1);
		
		if (philo->philo_id ==  philo->n_philo)
			philo->philo_id = 1;
		else
			(philo->philo_id)++;
	// } */
}

void	create_philos(t_prm *philo)
{
	pthread_t	thread_id[philo->n_philo];

	while (philo->philo_id <= philo->n_philo)
	{
		if (pthread_create(&thread_id[philo->philo_id - 1], NULL, (void*)work, philo) == -1)
		{
			perror("pthread");
			exit(1);
		}
		printf("hola\n");
		if (pthread_detach(thread_id[philo->philo_id - 1]))
			printf("---------------------------------detach fail\n");
		philo->philo_id++;
	}
}

int main(int argc, char **argv)
{
	t_time	time;
	t_prm	philo;
	//size_t		i = 0;

	if (argc == 5 || argc == 6)
	{
		time_parm(argv, &time, argc, &philo);
		printf("die=>%d eat=>%d sleep=>%d m_eat=>%d\n", time.die, time.eat, time.sleep, time.m_eat);
		make_mutex(&philo);
		create_philos(&philo);
		philo.current_time = get_time(philo);
	
		/* while (philo.current_time - philo.primary < philo.primary)
		{
			philo.current_time = get_time(philo);
			printf("TIME => %llu \n", philo.current_time - philo.primary);
		} */
	}
	
	else
		ft_putstr_fd("Not enough arguments\n", 2);
}
