/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:58:14 by meharit           #+#    #+#             */
/*   Updated: 2023/04/03 12:12:46 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	work(t_list *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		sem_wait(philo->info->forks);
		ft_printf("%lld ms philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		sem_wait(philo->info->forks);
		ft_printf("%lld ms philo %d has taken a fork\n", set_time(philo->info), philo->id, philo->info);
		ft_printf("%lld ms philo %d is eating\n", set_time(philo->info), philo->id, philo->info);
		philo->last_meal = set_time(philo->info);
		philo->n_eat++;
		// printf("philo %d =======> %d\n", philo->id, philo->n_eat);
		if (philo->n_eat == philo->info->m_eat)
		{
			sem_wait(philo->info->meal);
			philo->info->finished_eating++;
			sem_post(philo->info->meal);
		}
		// printf("finished_eating = %d\n", philo->info->finished_eating);
		if (philo->info->finished_eating == philo->info->n_philo)
		{
			printf("----------------------finished meals\n");
			exit (0);
		}

		usleep(philo->info->eat * 1000);
		ft_printf("%lld ms philo %d finished eating\n", set_time(philo->info), philo->id, philo->info);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		ft_printf("%lld ms philo %d is sleeping\n", set_time(philo->info), philo->id, philo->info);
		usleep(philo->info->sleep * 1000);
		ft_printf("%lld ms philo %d is thinking\n", set_time(philo->info), philo->id, philo->info);
	}
}

void	make_philos(t_prm *philo)
{
	int	*pid;
	int	i;

	i = 0;

	/////////// SEMAPHORES ////////////////
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->n_philo);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	philo->meal = sem_open("meal", O_CREAT, 0644, 1);
	///////////////////////////////////////

	philo->init = timer();
	pid = (int*)malloc(sizeof(int) * philo->n_philo);
	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);

	while (i < philo->n_philo)
	{
		//////// init /////////
		philo->p_list[i].id = i;
		philo->p_list[i].n_eat = 0;
		philo->p_list[i].last_meal = set_time(philo);
		philo->p_list[i].info = philo;
		///////////////////////
		pid[i] = fork();
		if (pid[i] == 0)
		{
			philo->p_list[i].id = i + 1;
			work(&philo->p_list[i]);
		}
		i++;
	}
	i = 0;
	while (i < philo->n_philo)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	check_meals(t_prm *philo)
{
	 while (1)
	 {
		if (philo->finished_eating == philo->n_philo)
		{
			printf("----------------------finished meals\n");
			exit (0);
		}
	 }
}

int main(int argc, char **argv)
{
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		sem_unlink("forks");
		sem_unlink("print");
		sem_unlink("meal");
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				printf("philo = %d die = %d eat = %d sleep = %d m_eat = %d\n", philo.n_philo, philo.die, philo.eat, philo.sleep, philo.m_eat);
				make_philos(&philo);
				printf("must_eat %d\n", philo.p_list[1].n_eat);
				// check_meals(&philo);
				sem_close(philo.forks);
				sem_close(philo.forks);
				sem_close(philo.meal);	
			}
		}
	}
}
