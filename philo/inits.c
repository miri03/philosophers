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

void	ft_printf( char *mess, unsigned long time, int id)
{
	pthread_mutex_t print;

	pthread_mutex_lock(&print);
	printf(mess, time, id);
	pthread_mutex_unlock(&print);
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
	// gettimeofday(&(philo->init), NULL);

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
