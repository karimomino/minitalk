# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 21:08:10 by kamin             #+#    #+#              #
#    Updated: 2022/03/02 03:21:33 by kamin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server

CLIENT   = client

CC	     = gcc
FLAGS    = -Wall -Werror -Wextra

#LIBS	 = -L./libft -lft
#LIBFT	 = libft.a

all : $(SERVER) $(CLIENT)

$(SERVER) :
	@$(CC) $(FLAGS) src/server.c -c
	@$(CC) server.o -o $@
	@printf "\033[0;32m./$@ successfully build\e[0m\n"

$(CLIENT) :
	@$(CC) $(FLAGS) src/client.c -c
	@$(CC) client.o -o $@
	@printf "\033[0;32m./$@ successfully build\e[0m\n"


clean :
	@rm -f *.o

fclean: clean
	@rm -f $(SERVER) $(CLIENT)

re: fclean all
