# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:05:30 by bahn              #+#    #+#              #
#    Updated: 2021/12/15 20:51:34 by bahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCFLAGS = -I./includes -I./libft $(CPPFLAGS)

RM = rm -fv

LIBFT_PATH = ./libft
LIBFT_LINK = -Llibft -lft

SRCS_PATH = ./srcs/
SRCS_NAME = main.c minishell.c \
			env_var.c handler.c parsing.c \
			change_dir.c argv_vector.c quotes.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

CMD_SRCS_PATH = ./srcs/command/
CMD_SRCS_NAME = echo.c
CMD_SRCS = $(addprefix $(CMD_SRCS_PATH), $(CMD_SRCS_NAME))
CMD_OBJS = $(CMD_SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(CMD_OBJS)
		$(MAKE) all -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(INCFLAGS) $^ $(LIBFT_LINK) $(LDFLAGS) -lreadline -o $@ 

clean : 
		$(MAKE) clean -C $(LIBFT_PATH)
		$(RM) $(OBJS) $(CMD_OBJS)

fclean : clean
		$(MAKE) fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re