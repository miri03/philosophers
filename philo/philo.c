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

// void	work(t_prm *philo)
// {
	
// 	if (philo->philo_id % 2 == 0)
// 		 usleep(1500);
	
// 	printf("%d\n", philo->philo_id);
	

// 	while (1)
// 	{
// 		if (pthread_mutex_lock(&(philo->fork[philo->philo_id - 1])) == 0)
// 			printf("philo %d has taken the fork %d \n", philo->philo_id, philo->philo_id - 1);
// 		else
// 		 printf("------------failed to take a fork\n");

// 		if (pthread_mutex_lock(&(philo->fork[philo->philo_id])) == 0)
// 			printf("philo %d has taken the fork %d\n", philo->philo_id, philo->philo_id);
// 		printf("philo %d is eating\n", philo->philo_id);

// 		usleep(philo->eat * 1000);
// 		printf("\nphilo %d finished eating\n", philo->philo_id);

// 		// printf("\nphilo %d is sleeping\n", philo->philo_id);
// 		// usleep(philo->sleep * 1000);


// 		if (pthread_mutex_unlock(&(philo->fork[philo->philo_id - 1])))
// 				printf("1 unlock failed\n");
// 		else
// 			printf("fork %d is in the table\n", philo->philo_id - 1);
		
// 		if (philo->philo_id ==  philo->n_philo)
// 			philo->philo_id = 1;
// 		else
// 			(philo->philo_id)++;
// 	}
// }

void	f_life(t_list *philo)
{
	while (1)
	{
		if (pthread_mutex_lock(philo->fork) == 0)
			printf("philo %d has taken the fork %d \n", philo->id, philo->id - 1);
		else
		 printf("------------failed to take a fork\n");

		if (pthread_mutex_lock((philo->next)->fork) == 0)
			printf("philo %d has taken the fork %d\n", philo->id, philo->id);
		printf("philo %d is eating\n", philo->id);

		// usleep(philo->eat * 1000);
		// printf("\nphilo %d finished eating\n", philo->philo_id);

		// printf("\nphilo %d is sleeping\n", philo->philo_id);
		// usleep(philo->sleep * 1000);


		if (pthread_mutex_unlock(philo->fork))
				printf("1 unlock failed\n");
		else
			printf("fork %d is in the table\n", philo->id - 1);
		
		// if (philo->philo_id ==  philo->n_philo)
		// 	philo->philo_id = 1;
		// else
		// 	(philo->philo_id)++;
	}
}

void	work(t_prm *philo)
{
	t_list *tmp;

	tmp = philo->p_list;
	while (tmp->id < philo->n_philo)
	{
		f_life(tmp);
		tmp = tmp->next;
	}
}

void	create_philos(t_prm *philo)
{
	(void)philo;
	// pthread_t	thread_id[philo->n_philo];

	// while (philo->philo_id <= philo->n_philo)
	// {
	// 	if (pthread_create(&thread_id[philo->philo_id - 1], NULL, (void*)work, philo) == -1)
	// 	{
	// 		perror("pthread");
	// 		exit(1);
	// 	}
	// 	if (pthread_detach(thread_id[philo->philo_id - 1]))
	// 		printf("---------------------------------detach fail\n");
	// 	philo->philo_id++;
	// }
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
//	printf("----------------%d\n", philo->tp.tv_usec);
	time = (philo->init.tv_sec - now.tv_sec) * 1000;
	// time = (philo->tp.tv_sec - now->tv_sec) + (philo->tp.tv_usec - now->tv_usec);
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
