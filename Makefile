# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:05:30 by bahn              #+#    #+#              #
#    Updated: 2022/01/05 12:30:21 by bahn             ###   ########.fr        #
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
SRCS_NAME = main.c minishell.c more_input.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

PROMPT_SRCS_PATH = ./srcs/prompt/
PROMPT_SRCS_NAME = prompt.c
PROMPT_SRCS = $(addprefix $(PROMPT_SRCS_PATH), $(PROMPT_SRCS_NAME))
PROMPT_OBJS = $(PROMPT_SRCS:.c=.o)

SIG_SRCS_PATH = ./srcs/signal/
SIG_SRCS_NAME = handler.c 
SIG_SRCS = $(addprefix $(SIG_SRCS_PATH), $(SIG_SRCS_NAME))
SIG_OBJS = $(SIG_SRCS:.c=.o)

CMD_SRCS_PATH = ./srcs/command/
CMD_SRCS_NAME = echo.c echo_for_execve.c \
				cd.c \
				pwd.c \
				export.c \
				unset.c \
				env.c \
				exit_status.c
CMD_SRCS = $(addprefix $(CMD_SRCS_PATH), $(CMD_SRCS_NAME))
CMD_OBJS = $(CMD_SRCS:.c=.o)

PARSE_SRCS_PATH = ./srcs/parse/
PARSE_SRCS_NAME = parsing.c \
					input_split.c \
					remove_enclosed_quotes.c \
					escape_sequence.c
PARSE_SRCS = $(addprefix $(PARSE_SRCS_PATH), $(PARSE_SRCS_NAME))
PARSE_OBJS = $(PARSE_SRCS:.c=.o)

ENVV_SRCS_PATH = ./srcs/envv/
ENVV_SRCS_NAME = envv.c
ENVV_SRCS = $(addprefix $(ENVV_SRCS_PATH), $(ENVV_SRCS_NAME))
ENVV_OBJS = $(ENVV_SRCS:.c=.o)

RIDIR_SRCS_PATH = ./srcs/redirection/
RIDIR_SRCS_NAME = set_redirection.c redirection_finder.c
RIDIR_SRCS = $(addprefix $(RIDIR_SRCS_PATH), $(RIDIR_SRCS_NAME))
RIDIR_OBJS = $(RIDIR_SRCS:.c=.o)

EXEC_SRCS_PATH = ./srcs/execve/
EXEC_SRCS_NAME = to_execve.c
EXEC_SRCS = $(addprefix $(EXEC_SRCS_PATH), $(EXEC_SRCS_NAME))
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

UTILS_SRCS_PATH = ./srcs/utils/
UTILS_SRCS_NAME = execfile_finder.c \
					argv_counter.c \
					split_free.c \
					command_free.c \
					incorrect_exit.c
UTILS_SRCS = $(addprefix $(UTILS_SRCS_PATH), $(UTILS_SRCS_NAME))
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

ALL_OBJS = $(OBJS) \
			$(SIG_OBJS) \
			$(PROMPT_OBJS) \
			$(CMD_OBJS) \
			$(PARSE_OBJS) \
			$(ENVV_OBJS) \
			$(RIDIR_OBJS) \
			$(EXEC_OBJS) \
			$(UTILS_OBJS)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME) : $(ALL_OBJS)
		git submodule update --init --recursive
		$(MAKE) all bonus -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(INCFLAGS) $^ $(LIBFT_LINK) $(LDFLAGS) -lreadline -o $@

clean : 
		$(MAKE) clean -C $(LIBFT_PATH)
		$(RM) $(ALL_OBJS)

fclean : clean
		$(MAKE) fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re