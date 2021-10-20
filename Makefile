# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:05:30 by bahn              #+#    #+#              #
#    Updated: 2021/10/20 19:49:15 by bahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCFLAGS = -I./includes -I./libft -I./get_next_line

RM = rm -fv

LIBFT_PATH = ./libft
LIBFT_LINK = -Llibft -lft

GNL_PATH = ./get_next_line/
GNL_SRCS = $(addprefix $(GNL_PATH), get_next_line.c)
GNL_OBJS = $(GNL_SRCS:.c=.o)

SRCS_PATH = ./srcs/
SRCS_NAME = minishell.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_LINK) -c $< -o $@

$(NAME) : $(OBJS) $(GNL_OBJS)
		$(MAKE) all -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $^ $(INCFLAGS) $(LIBFT_LINK) -o $@ 

clean : 
		$(MAKE) clean -C $(LIBFT_PATH)
		$(RM) $(OBJS)

fclean : clean
		$(MAKE) fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re