/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:18:05 by meharit           #+#    #+#             */
/*   Updated: 2023/04/10 00:49:39 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	count;

	count = 0;
	while (s1[count] != '\0' || s2[count] != '\0')
	{
		if (s1[count] != s2[count])
			return (s1[count] - s2[count]);
		count++;
	}
	return (0);
}

void	ft_printf(char *mess, long long time, int id, t_prm *philo)
{
	sem_wait(philo->print);
	printf(mess, time, id);
	sem_post(philo->print);
}

void	init(t_prm *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		philo->p_list[i].i_die = philo->die;
		philo->p_list[i].id = i;
		philo->p_list[i].n_eat = 0;
		philo->p_list[i].info = philo;
		philo->p_list[i].last_meal = set_time(philo);
		i++;
	}
}

void	make_semaphores(t_prm *philo)
{
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->n_philo);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
}

void	ft_wait(t_prm *philo, int *pid)
{
	int	i;
	int	g;

	waitpid(-1, &g, 0);
	if (WEXITSTATUS(g) == 0)
	{
		i = 0;
		while (i < philo->n_philo)
		{
			waitpid(-1, &g, 0);
			i++;
		}
	}
	if (WEXITSTATUS(g))
	{
		i = 0;
		ft_printf("%lld ms philo %d is dead\n",
			set_time(philo), WEXITSTATUS(g), philo);
		while (i < philo->n_philo)
			kill(pid[i++], SIGKILL);
	}
	free(philo->p_list);
	free(pid);
}
