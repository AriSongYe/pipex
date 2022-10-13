# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 15:01:04 by yecsong           #+#    #+#              #
#    Updated: 2022/10/12 15:01:06 by yecsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := get_next_line.a

SRCS := get_next_line.c\
		get_next_line_utils.c\

OBJS = $(SRCS:%.c=%.o)

AR := ar

ARFLAGS := src

CC := cc

CFLAGS := -Werror -Wextra -Wall

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

re :
	make fclean
	make all

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)
.PHONY : all clean fclean bonus re
