/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:10:04 by meharit           #+#    #+#             */
/*   Updated: 2023/04/08 05:09:17 by meharit          ###   ########.fr       */
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

void	sleepi(int x)
{
	struct timeval	start;
	struct timeval	end;
	int				time;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&end, NULL);
		time = (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
				+ start.tv_usec / 1000);
		if (x <= time)
			break ;
	}
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
	int	d;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			d = -1;
			if (j == 0)
				d = 0;
			if (!ft_isdigit2(argv[i][j], d))
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
