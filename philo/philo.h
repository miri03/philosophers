/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:07:34 by meharit           #+#    #+#             */
/*   Updated: 2023/04/08 20:11:01 by meharit          ###   ########.fr       */
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

# define RED "\e[0;31m"
# define RESET "\e[0m"

# define FAIL 1
# define SUCESS 0

typedef struct s_philo	t_prm;

typedef struct s_list
{
	int				id;
	pthread_t		thread_id;
	int				n_eat;
	long long		last_meal;
	t_prm			*info;
	pthread_mutex_t	*fork;
}				t_list;

typedef struct s_philo
{
	int				n_philo;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	t_list			*p_list;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	int				finished_eating;
	int				end;
	long long		init;

}				t_prm;

int				check_info(t_prm philo);
void			sleepi(int x);
void			free_destroy(t_prm *philo);
int				time_parm(char **argv, int argc, t_prm *philo);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
int				ft_isalpha(int c);
void			ft_printf( char *mess, long long time, int id, t_prm *philo);
long long		set_time(t_prm *philo);
long long		timer(void);
void			ft_eat(t_list *philo);
int				check_is_digit(char **argv, int argc);
int				ft_isdigit2(int c, int d);
int				must_eat(t_prm *philo);

#endif
