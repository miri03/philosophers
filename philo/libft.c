/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:26:17 by meharit           #+#    #+#             */
/*   Updated: 2023/04/08 05:06:48 by meharit          ###   ########.fr       */
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

int	ft_isdigit2(int c, int d)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (d == 0 && (c == '+' || c == '-'))
		return (1);
	return (0);
}
