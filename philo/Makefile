# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 14:13:03 by edegraev          #+#    #+#              #
#    Updated: 2024/07/04 09:33:53 by edegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -g #Wall -Werror -Wextra
SRC = ft.c init.c atoll.c main.c monitor.c philo.c time.c utils.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norme:
	norminette

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
