/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:07:34 by meharit           #+#    #+#             */
/*   Updated: 2023/03/01 22:16:37 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
#include <unistd.h>

typedef struct s_list
{
	int				id;
	int				n_eat;
	pthread_t		thread_id;
	struct s_list	*next;

}				t_list;

typedef struct s_philo
{
	int				philo_id;
	int				n_philo;
	int				current_time;
	int				primary;
	pthread_mutex_t	*fork;
	t_list		*p_list;
}				t_prm;

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
	int	m_eat;
}			t_time;

int		ft_atoi(const char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(int content);
void	ft_putstr_fd(char *s, int fd);

#endif
