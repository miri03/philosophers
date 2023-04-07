/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:58:14 by meharit           #+#    #+#             */
/*   Updated: 2023/04/07 21:55:22 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/semaphore.h>

void	*check_death(void *arg)
{
	t_list *philo;

	philo = (t_list *)arg;
	while (1)
	{
		sem_wait(philo->info->death);
		if (set_time(philo->info->init) - philo->info->die > philo->last_meal)
		{
			sem_post(philo->info->death);
			printf("-----------DEAD----------\n");
			exit (philo->id);
		}
		sem_post(philo->info->death);
		usleep(1000);
	}
	return (NULL);
}

void	work(t_list *philo)
{
	pthread_t	t1;

	if (philo->id % 2 == 0)
		usleep(1000);

	sem_wait(philo->info->death);
	pthread_create(&t1, NULL, check_death, philo);
	sem_post(philo->info->death);
	while (1)
	{
		sem_wait(philo->info->forks);
		ft_printf("%lld ms philo %d has taken a fork\n", set_time(philo->i_init), philo->id, philo->info);
		sem_wait(philo->info->forks);
		ft_printf("%lld ms philo %d has taken a fork\n", set_time(philo->i_init), philo->id, philo->info);
		ft_printf("%lld ms philo %d is eating\n", set_time(philo->i_init), philo->id, philo->info);
		philo->last_meal = set_time(philo->info->init);

		// printf("++++++++++++++++++++++++++++%p\n", &philo->last_meal);
		philo->n_eat++;
		if (philo->n_eat == philo->info->m_eat)
		{
			printf("[%d == %d]DONE\n", philo->id, philo->n_eat);
			sem_post(philo->info->forks);
			sem_post(philo->info->forks);
			exit (0);
		}
		usleep(philo->info->eat * 1000);
		ft_printf("%lld ms philo %d finished eating\n", set_time(philo->i_init), philo->id, philo->info);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		ft_printf("%lld ms philo %d is sleeping\n", set_time(philo->i_init), philo->id, philo->info);
		usleep(philo->info->sleep * 1000);
		ft_printf("%lld ms philo %d is thinking\n", set_time(philo->i_init), philo->id, philo->info);
	}
	pthread_join(t1, NULL);
}

void	make_philos(t_prm *philo)
{
	int	*pid;
	int	i;

	i = 0;

	philo->p_list = malloc(sizeof(t_list) * philo->n_philo);
	pid = (int*)malloc(sizeof(int) * philo->n_philo);
	philo->init = timer();

	/////////// SEMAPHORES ////////////////
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->n_philo);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	philo->meal = sem_open("meal", O_CREAT, 0644, 1);
	philo->death = sem_open("death", O_CREAT, 0644, 1);
	///////////////////////////////////////

	while (i < philo->n_philo)
	{
		//////// init /////////

		philo->p_list[i].i_die = philo->die;
		philo->p_list[i].i_init = philo->init;



		philo->p_list[i].id = i;
		philo->p_list[i].n_eat = 0;
		philo->p_list[i].info = philo;



		philo->p_list[i].last_meal = set_time(philo->init);

		///////////////////////
		pid[i] = fork();
		if (pid[i] == 0)
		{	
			philo->p_list[i].id = i + 1;
			work(&philo->p_list[i]);
			exit (0);
		}
		i++;
	}
	/* i = 0;
	while (i < philo->n_philo)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	} */

	int g;
	waitpid(-1, &g, 0);
	//printf("---->%d\n", WEXITSTATUS(g));
	if (!WEXITSTATUS(g))
	{
		i = 0;
		while (i < philo->n_philo)
		{
			waitpid(-1, &g, 0);
			//printf("---->%d\n", WEXITSTATUS(g));
			if (WEXITSTATUS(g))
				break;
			i++;
		}
	}
	if (WEXITSTATUS(g))
	{
		i = 0;
		ft_printf("%lld ms philo %d is dead\n", set_time(philo->init), WEXITSTATUS(g), philo);
		while (i < philo->n_philo)
			kill(pid[i++], SIGKILL);
	}
}

int main(int argc, char **argv)
{
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		sem_unlink("death");
		sem_unlink("forks");
		sem_unlink("print");
		sem_unlink("meal");
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				printf("philo = %d | die = %d | eat = %d | sleep = %d | m_eat = %d\n", philo.n_philo, philo.die, philo.eat, philo.sleep, philo.m_eat);
				make_philos(&philo);
				sem_close(philo.forks);
				sem_close(philo.forks);
				sem_close(philo.meal);	
			}
		}
	}
	else
		ft_putstr_fd(RED "Wrong number of arguments\n" RESET, 2);
}
