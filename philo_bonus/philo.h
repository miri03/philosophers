/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:58:37 by meharit           #+#    #+#             */
/*   Updated: 2023/04/03 12:12:04 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <semaphore.h>

# define RED "\e[0;31m"
# define RESET "\e[0m"

typedef struct s_philo	t_prm;

typedef struct s_list
{
	int				id;
	pthread_t		thread_id;
	int				n_eat;
	long long		last_meal;
	t_prm			*info;
}				t_list;

typedef struct s_philo
{
	int				n_philo;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	t_list			*p_list;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal;
	int				finished_eating;
	int				end;
	long long		init;

}				t_prm;

int			ft_atoi(const char *str);
int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
int			check_info(t_prm philo);
int			time_parm(char **argv, int argc, t_prm *philo);
int			ft_isalpha(int c);
long long	set_time(t_prm *philo);
long long	timer(void);
void		ft_printf(char *mess, long long time, int id, t_prm *philo);

#endif
