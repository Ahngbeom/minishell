/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:04:38 by bahn              #+#    #+#             */
/*   Updated: 2022/01/14 14:57:20 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EOT 4
# define LF	10

# define READ 0
# define WRITE 1

# define KEY 0
# define VALUE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10
# endif

# define PIPE "|"
# define TRNC_REDIR ">"
# define APND_REDIR ">>"
# define R_TRNC_REDIR "<"
# define R_APND_REDIR "<<"

# include <unistd.h>			// fork()
# include <signal.h>			// signal()
# include <stdio.h>				// printf()
# include <readline/readline.h> // readline()
# include <readline/history.h>	// add_history
# include <termios.h> 			// tcgetattr()
# include <sys/wait.h>			// wait(), waitpid(), wait3(), wait4()
# include <fcntl.h>				// open()
# include <sys/stat.h>			// stat()
# include <errno.h>				// errno
# include "functions.h"

#endif