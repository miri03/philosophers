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

unsigned long	timer()
{
	struct timeval	time;
	unsigned long	ret;

	gettimeofday(&time, NULL);
	
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

unsigned long	set_time(t_prm *philo)
{
	unsigned long now;
	unsigned long ret;

	now = timer();
	ret = now - philo->init;
	return (ret);
}
