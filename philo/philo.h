/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:07:34 by meharit           #+#    #+#             */
/*   Updated: 2023/03/22 17:18:04 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

#define RED "\e[0;31m"
#define reset "\e[0m"

typedef struct s_philo t_prm;

typedef struct s_list
{
	int			id;
	pthread_t	*thread_id;
	int			n_eat;
	
	long long	last_meal;
	t_prm		*info;
}				t_list;

typedef struct s_philo
{

	int				n_philo;

	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	
	t_list		*p_list;

	pthread_mutex_t	*fork;

	struct timeval init;
	struct timeval start;

	struct timeval end;

}				t_prm;

// typedef struct s_time
// {
// 	int	die;
// 	int	eat;
// 	int	sleep;
// 	int	m_eat;
// }			t_time;

int		ft_atoi(const char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(int content);
void	ft_putstr_fd(char *s, int fd);
int		ft_isalpha(int c);

#endif
