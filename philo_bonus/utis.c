/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:44 by meharit           #+#    #+#             */
/*   Updated: 2023/04/08 05:03:52 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	time_parm(char **argv, int argc, t_prm *philo)
{
	philo->p_list = NULL;
	philo->m_eat = -1;
	philo->end = 1;
	philo->finished_eating = 0;
	if (!check_is_digit(argv, argc))
		return (0);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
		philo->m_eat = ft_atoi(argv[5]);
	if (argc == 5 && philo->m_eat == -1)
		philo->m_eat = INT_MAX;
	philo->n_philo = ft_atoi(argv[1]);
	philo->init = timer();
	return (1);
}

int	check_info(t_prm philo)
{
	if (philo.n_philo <= 0 || philo.die <= 0
		|| philo.eat <= 0 || philo.sleep <= 0 || philo.m_eat <= 0)
	{
		printf(RED "invalid parameters\n" RESET);
		return (0);
	}
	return (1);
}

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
