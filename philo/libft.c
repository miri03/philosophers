/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:26:17 by meharit           #+#    #+#             */
/*   Updated: 2023/03/01 22:16:28 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL && fd >= 0)
		write(fd, s, ft_strlen(s));
}

int	check_info(t_prm philo)
{
	if (philo.n_philo < 0 || philo.die < 0
		|| philo.eat < 0 || philo.sleep < 0 || philo.m_eat < 0)
	{
		printf(RED "invalid parameters\n" RESET);
		return (0);
	}
	return (1);
}
