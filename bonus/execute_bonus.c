/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:51:47 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/20 14:55:39 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_line(t_info **info, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror_exit("Error : pipe function");
	pid = fork();
	if (pid == -1)
		perror_exit("Error : fork function");
	child_exec(info, argv, fd, pid);
	parent_exec(info, argv, fd, pid);
}

void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		in_fd;
	int		temp_fd;

	if (pid == 0 && (*info)->is_heredoc == 1 && (*info)->i == 1)
	{
		close(fd[0]);
		temp_fd = open("/tmp/temp_pipex", O_RDONLY);
		dup2(temp_fd, 0);
		dup2(fd[1], 1);
		execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
	}
	else if (pid == 0 && (*info)->i == 0)
	{
		close(fd[0]);
		in_fd = open(argv[1], O_RDONLY);
		dup2(in_fd, 0);
		dup2(fd[1], 1);
		execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
	}
}

void	parent_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		o;
	char	*temp;

	if (pid > 0 && (*info)->i == (*info)->argc - 4)
	{
		close(fd[1]);
		if ((*info)->is_heredoc != 1)
			o = open(argv[(*info)->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		else
			o = open(argv[(*info)->argc - 1],
					O_CREAT | O_RDWR | O_APPEND, 0644);
		if (o == -1)
			perror_exit("Error : open file Error");
		temp = read_fd(fd[0]);
		write(o, temp, ft_strlen(temp));
		if (temp && temp[0] != '\0')
			free(temp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, WNOHANG);
	}
}
