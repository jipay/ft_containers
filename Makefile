# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 18:53:23 by jdidier           #+#    #+#              #
#    Updated: 2022/04/06 16:07:52 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

SRC			= main.cpp \

OBJ			= $(SRC:.cpp=.o)
DEP			= $(OBJ:.o=.d)

CC			= c++
FLAGS		= -Wall -Werror -Wextra -std=c++98

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

-include $(DEP)

%.o:%.cpp
	$(CC) -MMD $(FLAGS) -c $< -o $@

clean:
			rm -f $(OBJ) $(DEP)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re