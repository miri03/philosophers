# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meharit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 14:28:00 by meharit           #+#    #+#              #
#    Updated: 2023/04/09 21:04:48 by meharit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf

CFILES = philo.c \
		 ft_atoi.c \
		 libft.c \
		 utis.c \
		 utis2.c \

OFILES = philo.o \
		 ft_atoi.o \
		 libft.o \
		 utis.o \
		 utis2.o \

all: $(NAME)

$(NAME) : $(OFILES)
	cc -lpthread $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	$(RM) $(OFILES)

fclean : clean
	$(RM) $(NAME)

re: fclean all
