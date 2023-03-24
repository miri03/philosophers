# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meharit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 14:28:00 by meharit           #+#    #+#              #
#    Updated: 2023/03/22 15:42:14 by meharit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf

CFILES = philo.c \
		 ft_atoi.c \
		 libft.c \

OFILES = philo.o \
		 ft_atoi.o \
		 libft.o \

all: $(NAME)

$(NAME) : $(OFILES)
	cc -lpthread -fsanitize=thread -g $(CFLAGS) $(OFILES) -o $(NAME)
#	cc -lpthread $(CFLAGS) $(OFILES) -o $(NAME)

debug: $(OFILES) 
	cc -lpthread -fsanitize=address -g $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	$(RM) $(OFILES)

fclean : clean
	$(RM) $(NAME)

re: fclean all
