#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

int		main(int argc, char *argv[])
{
	int	fd = open("hihi", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	execve("/bin/ls", argv, NULL);
	close(fd);
	return (0);
}