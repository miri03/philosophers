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

int main(int argc, char **argv)
{
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		if (time_parm(argv, argc, &philo))
		{
			if (check_info(philo))
			{
				