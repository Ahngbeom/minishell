# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:05:30 by bahn              #+#    #+#              #
#    Updated: 2022/01/01 22:32:55 by bahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-g
INCFLAGS = -I./includes -I./libft $(CPPFLAGS)

RM = rm -fv

LIBFT_PATH = ./libft
LIBFT_LINK = -Llibft -lft

SRCS_PATH = ./srcs/
SRCS_NAME = main.c minishell.c prompt.c to_execve.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

CMD_SRCS_PATH = ./srcs/command/
CMD_SRCS_NAME = echo.c echo_for_execve.c \
				cd.c \
				pwd.c \
				export.c \
				unset.c \
				envv.c \
				exit_status.c
CMD_SRCS = $(addprefix $(CMD_SRCS_PATH), $(CMD_SRCS_NAME))
CMD_OBJS = $(CMD_SRCS:.c=.o)

PARSE_SRCS_PATH = ./srcs/parse/
PARSE_SRCS_NAME =  parsing.c \
					redirection_finder.c \
					input_split.c \
					remove_enclosed_quotes.c \
					escape_sequence.c
PARSE_SRCS = $(addprefix $(PARSE_SRCS_PATH), $(PARSE_SRCS_NAME))
PARSE_OBJS = $(PARSE_SRCS:.c=.o)

SIG_SRCS_PATH = ./srcs/signal/
SIG_SRCS_NAME = handler.c 
SIG_SRCS = $(addprefix $(SIG_SRCS_PATH), $(SIG_SRCS_NAME))
SIG_OBJS = $(SIG_SRCS:.c=.o)

UTILS_SRCS_PATH = ./srcs/utils/
UTILS_SRCS_NAME = execfile_finder.c \
					argv_counter.c \
					split_free.c \
					command_free.c \
					incorrect_exit.c
UTILS_SRCS = $(addprefix $(UTILS_SRCS_PATH), $(UTILS_SRCS_NAME))
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(CMD_OBJS) $(PARSE_OBJS) $(SIG_OBJS) $(UTILS_OBJS)
		git submodule update --init --recursive
		$(MAKE) all bonus -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(INCFLAGS) $^ $(LIBFT_LINK) $(LDFLAGS) -lreadline -o $@

clean : 
		$(MAKE) clean -C $(LIBFT_PATH)
		$(RM) $(OBJS) $(CMD_OBJS) $(PARSE_OBJS) $(SIG_OBJS) $(UTILS_OBJS)

fclean : clean
		$(MAKE) fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re