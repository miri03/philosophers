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

void    sleepi(int x)
{
    struct timeval    start;
    struct timeval    end;
    int                time;

    gettimeofday(&start, NULL);
    while (1)
    {
        usleep(100);
        gettimeofday(&end, NULL);
        time = (end.tv_sec * 1000 + end.tv_usec / 1000)
            - (start.tv_sec * 1000 + start.tv_usec / 1000);
        if (x <= time)
            break ;
    }
}

void	work(void *arg)
{
	t_list *philo;

	philo = (t_list*)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (pthread_mutex_lock(&(philo->info->fork[philo->id - 1])) == 0)
		{
			ft_printf("[%lu] philo %d has taken a fork\n", timer() - philo->info->init, philo->id);
			printf("fork %d\n", philo->id - 1);
		}
		else
			printf("------------[%d]failed to take a fork\n", philo->id);
		if (pthread_mutex_lock(&(philo->info->fork[philo->id % philo->info->n_philo])) == 0)
		{
			ft_printf("[%d] philo %d has taken a fork\n", timer() - philo->info->init, philo->id);
			printf("fork %d\n", philo->id % philo->info->n_philo);
		}
		else
			printf("------------[%d]failed to take a fork\n", philo->id);
		ft_printf("[%lu] philo %d is eating\n",set_time(philo->info), philo->id);

		sleepi(philo->info->eat);
		ft_printf("[%lu] philo %d finished eating\n", set_time(philo->info), philo->id);

		if (pthread_mutex_unlock(&(philo->info->fork[philo->id - 1])))
				printf("%d unlock failed\n", philo->id);
		else
			printf("fork %d is in the table\n", philo->id - 1);
		
		if (pthread_mutex_unlock(&(philo->info->fork[philo->id % philo->info->n_philo])))
				printf("%d unlock failed\n", philo->id);
		else
			printf("fork %d is in the table\n", philo->id);

		// printf("\nphilo %d is sleeping\n", philo->philo_id);
		// usleep(philo->sleep * 1000);

		// if (philo->philo_id ==  philo->n_philo)
		// 	philo->philo_id = 1;
		// else
		// 	(philo->philo_id)++;
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
		philo->p_list[i].id = i+1;
		philo->p_list[i].info = philo;
		pthread_create(&(philo->p_list[i].thread_id), NULL, (void*)work, &philo->p_list[i]);
		pthread_detach(philo->p_list[i].thread_id);
		i++;
	}
}

void	make_mutex(t_prm *philo)
{
	int	i;

	i = 0;
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	while (i < philo->n_philo)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL) == -1)
			printf("mutex init has failed\n");
		i++;
	}
}

int	check_info(t_prm philo)
{
	if (philo.n_philo < 0 || philo.die < 0 || philo.eat < 0 | philo.sleep < 0 | philo.m_eat < 0)
	{
		printf(RED"invalid parameters\n"reset);
		return (0);
	}

	// if (philo.die < 60 | philo.eat < 60 | philo.sleep < 60)
	// {
	// 	printf(RED"Please change this time parameters\n"reset);
	// 	return (0);
	// }
	return (1);
}

int main(int argc, char **argv)
{
	t_prm	philo;
	// int		i;

	// i = 0;
	if (argc == 5 || argc == 6)
	{
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				printf("die=>%d eat=>%d sleep=>%d m_eat=>%d\n", philo.die, philo.eat, philo.sleep, philo.m_eat);
				make_mutex(&philo);
				create_philos(&philo);
				// usleep(100);
			}
		}
		// while (i < philo.n_philo)
		// {
		// 	pthread_join(philo.p_list[i].thread_id, NULL);
		// 	i++;
		// }
	}
	else
		ft_putstr_fd(RED"Wrong number of arguments\n"reset, 2);
}
