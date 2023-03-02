/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:05:17 by meharit           #+#    #+#             */
/*   Updated: 2023/03/02 14:11:00 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_prm philo)
{
	struct timeval fn_time;
	int				current_time;

	gettimeofday(&fn_time, NULL);
	current_time = (fn_time.tv_sec * 1000) - philo.primary;
	return (current_time);
}

void	time_parm(char **argv, t_time *time, int argc, t_prm *philo)
{
	struct timeval fn_time;

	gettimeofday(&fn_time, NULL);
	time->m_eat = 0;
	time->die = ft_atoi(argv[2]);
	time->eat = ft_atoi(argv[3]);
	time->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		time->m_eat = ft_atoi(argv[5]);
	philo->p_list = NULL;
	philo->primary = (fn_time.tv_sec * 1000);
	philo->n_philo = ft_atoi(argv[1]);
}

void	work(t_prm *philo)
{
	(void) philo;
	while (1)
	{


	printf("correct\n");
}

void	create_philos(t_prm *philo)
{
	pthread_t	thread_id[philo->n_philo];
	int			i;
	int			rc;

	i = 1;
	while (i <= philo->n_philo)
	{
		rc = pthread_create(&thread_id[i-1], NULL, (void*)work, philo);
		if(rc == -1)
		{
			perror("pthread");
			exit(1);
		}
		ft_lstadd_back(&(philo->p_list), ft_lstnew(i));
		philo->p_list->thread_id = thread_id[i-1];
		i++;
	}
}

int main(int argc, char **argv)
{
	t_time	time;
	t_prm	philo;

	if (argc == 5 || argc == 6)
	{
		time_parm(argv, &time, argc, &philo);
		printf("%d %d %d %d\n", time.die, time.eat, time.sleep, time.m_eat);
		create_philos(&philo);
		philo.current_time = get_time(philo);

		/* while (1)
		{
			philo.current_time = get_time(philo);
			printf("%d\n", philo.current_time);
		} */

		while (philo.p_list)
		{
			printf("%d\n", philo.p_list->n_eat);
			philo.p_list = philo.p_list->next;
		}
	}
	else
		ft_putstr_fd("Not enough arguments\n", 2);
}
