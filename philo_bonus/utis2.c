/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:18:05 by meharit           #+#    #+#             */
/*   Updated: 2023/04/04 21:18:06 by meharit          ###   ########.fr       */
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
    // if (ft_strcmp(mess, "%lld ms philo %d is eating\n") == 0)
    // {
    //     philo->finished_eating
    // }
	printf(mess, time, id);
    sem_post(philo->print);
}