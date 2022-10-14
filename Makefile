# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 15:05:16 by yecsong           #+#    #+#              #
#    Updated: 2022/10/14 13:37:10 by yecsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

SRCS := main.c\
		execute.c\
		execute_2.c\
		utils.c\
		check_file.c\
		parsing.c

AR := ar

ARFLAGS := src

CC := cc

CFLAGS := -Werror -Wextra -Wall

all : $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C ./libft all
		$(MAKE) -C ./get_next_line all
		cp ./libft/libft.a ./$(NAME)
		$(CC) $(CFLAGS) $(SRCS) ./libft/libft.a ./get_next_line/get_next_line.a -o pipex

re : fclean all

clean :
	rm -f *.o
	rm -f libft/*.o
	rm -f get_next_line/*.o

fclean : clean
	rm -f $(NAME)
	rm -f libft/libft.a
	rm -f get_next_line/get_next_line.a

bonus :
	@make BONUS_CHECK=1 all

.PHONY : all clean fclean bonus re
