/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 22:34:10 by meharit           #+#    #+#             */
/*   Updated: 2023/03/25 22:34:12 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(char *mess, long long time, int id, t_prm *philo)
{
	if (pthread_mutex_lock(&philo->print))
		printf("lock fail [%s]\n", mess);

	// if (!philo->died)
		printf(mess, time, id);

	if (pthread_mutex_unlock(&philo->print))
		printf("unlock fail [%s]\n", mess);
}

int	check_info(t_prm philo)
{
	if (philo.n_philo < 0 || philo.die < 0
		|| philo.eat < 0 | philo.sleep < 0 | philo.m_eat < 0)
	{
		printf(RED "invalid parameters\n" reset);
		return (0);
	}
	return (1);
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
	philo->m_eat = 0;
	if (!check_is_digit(argv, argc))
		return (0);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);

	philo->died = 0;

	if (argc == 6)
		philo->m_eat = ft_atoi(argv[5]);
	philo->n_philo = ft_atoi(argv[1]);
	return (1);
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