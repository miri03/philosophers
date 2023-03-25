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

int	check_is_digit(char **argv, int argc)
{
	int	j;
	int	i;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isalpha(argv[i][j]))
			{
				printf(RED"Non digit parameter\n"reset);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	time_parm(char **argv, int argc, t_prm *philo)
{
	philo->p_list = NULL;
	gettimeofday(&(philo->init), NULL);

	philo->m_eat = 0;
	if (!check_is_digit(argv, argc))
		return (0);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);

	if (argc == 6)
		philo->m_eat = ft_atoi(argv[5]);
	philo->n_philo = ft_atoi(argv[1]);
	return (1);
}

void	work(void *arg)
{
	t_list *philo;

	philo = (t_list*)arg;
	while (1)
	{
		if (pthread_mutex_lock(&(philo->info->fork[philo->id])) == 0)
			ft_printf("[%lu] philo %d has taken a fork\n", set_time(philo->info), philo->id);
		else
		 printf("------------failed to take a fork\n");

		if (pthread_mutex_lock(&(philo->info->fork[philo->id + 1 % philo->info->n_philo])) == 0)
			ft_printf("[%d] philo %d has taken a fork\n", set_time(philo->info), philo->id);
		printf("philo %d is eating\n", philo->id);
		ft_printf("[%lu] philo %d is eating\n",set_time(philo->info), philo->id);
		// usleep(philo->eat * 1000);
		// printf("\nphilo %d finished eating\n", philo->philo_id);

		// printf("\nphilo %d is sleeping\n", philo->philo_id);
		// usleep(philo->sleep * 1000);

		if (pthread_mutex_unlock(&(philo->info->fork[philo->id])))
				printf("1 unlock failed\n");
		else
			printf("fork %d is in the table\n", philo->id - 1);
		
		if (pthread_mutex_unlock(&(philo->info->fork[philo->id + 1 % philo->info->n_philo])))
				printf("1 unlock failed\n");
		else
			printf("fork %d is in the table\n", philo->id - 1);

		// if (philo->philo_id ==  philo->n_philo)
		// 	philo->philo_id = 1;
		// else
		// 	(philo->philo_id)++;
	}
}

void	ft_printf( char *mess, unsigned long time, int id)
{
	pthread_mutex_t print;

	pthread_mutex_lock(&print);
	printf(mess, time, id);
	pthread_mutex_unlock(&print);
}

void	create_philos(t_prm *philo)
{
	int	i;

	i = 0;
	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);
	if (philo->p_list == NULL)
		printf("failed to allocet for philos\n");
	gettimeofday(&(philo->init), NULL);
	while (i <= philo->n_philo)
	{
		if (pthread_create(&(philo->p_list[i].thread_id), NULL, (void*)work, &philo->p_list[i]) == -1)
		{
			perror("pthread");
			exit(1);
		}
		i++;
	}
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	printf("\n");
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
			printf("mutex init has failed\n");
		printf("forks ========> %d\n", i+1);
		i++;
	}
	printf("\n");
}

unsigned long	set_time(t_prm *philo)
{
	unsigned long time;
	struct timeval now;

	gettimeofday(&now, NULL);
	time = (philo->init.tv_sec - now.tv_sec) * 1000 + (philo->init.tv_usec - now.tv_usec) / 1000;
	return (time);
}

int	check_info(t_prm philo)
{
	if (philo.n_philo < 0 || philo.die < 0 || philo.eat < 0 | philo.sleep < 0 | philo.m_eat < 0)
	{
		printf(RED"invalid parameters\n"reset);
		return (0);
	}

	if (philo.die < 60 | philo.eat < 60 | philo.sleep < 60)
	{
		printf(RED"Please change this time parameters\n"reset);
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				printf("die=>%d eat=>%d sleep=>%d m_eat=>%d\n", philo.die, philo.eat, philo.sleep, philo.m_eat);
				make_mutex(&philo);
				create_philos(&philo);
				usleep(100);
				printf("-----------------------%lu\n", set_time(&philo));
			}
		}
	}
	else
		ft_putstr_fd(RED"Wrong number of arguments\n"reset, 2);
}
