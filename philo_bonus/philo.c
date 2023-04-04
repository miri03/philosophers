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

void	work(t_prm *philo)
{
	
}

void	make_philos(t_prm *philo)
{
	int	*pid;
	int	i;

	i = 0;
	pid = (int*)malloc(sizeof(int) * philo->n_philo);
	while (i < philo->n_philo)
	{
		pid[i] = fork();
		if (pid[i])
			work(philo);
		i++;
	}
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
				make_philos(&philo);

			}
		}
	}
}