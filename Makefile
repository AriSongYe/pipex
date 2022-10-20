# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 15:05:16 by yecsong           #+#    #+#              #
#    Updated: 2022/10/19 20:53:05 by yecsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

BONUS_SRCS := bonus/pipex_bonus.c\
		bonus/execute_bonus.c\
		bonus/utils_bonus.c\
		bonus/check_file_bonus.c\
		bonus/parsing_bonus.c

SRCS := mandatory/pipex.c\
		mandatory/execute.c\
		mandatory/utils.c\

CC := cc

CFLAGS := -Werror -Wextra -Wall

all : $(NAME)

ifdef BONUS_CHECK
SRCS_FILES = $(BONUS_SRCS)
else
SRCS_FILES = $(SRCS)
endif

$(NAME) :
		$(MAKE) -C ./libft all
		$(MAKE) -C ./get_next_line all
		$(CC) $(CFLAGS) $(SRCS_FILES) ./libft/libft.a ./get_next_line/get_next_line.a -o pipex

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
