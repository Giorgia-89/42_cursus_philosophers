# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 09:19:56 by gd-innoc          #+#    #+#              #
#    Updated: 2023/11/26 10:30:06 by gd-innoc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = src/actions src/exit src/init src/lock src/main src/monitor src/utils

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread #-fsanitize=thread
RM = rm -fr

all: $(NAME)

$(NAME): $(SRC:=.o)
	$(CC) $(CFLAGS) $(SRC:=.o) -o $(NAME)

# $@: represents the target of the rule (object files)
# $<: represents the first prerequisite of the rule (source files)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRC:=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all
