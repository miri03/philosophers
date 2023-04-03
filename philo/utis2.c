/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 22:29:26 by meharit           #+#    #+#             */
/*   Updated: 2023/03/25 22:29:27 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timer(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	set_time(t_prm *philo)
{
	long long	now;

	now = timer();
	return (now - philo->init);
}

void	free_destroy(t_prm *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print);
	free(philo->fork);
	free(philo->p_list);
}

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
				printf(RED "Non digit parameter\n" RESET);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
