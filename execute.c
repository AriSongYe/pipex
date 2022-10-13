/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:51:47 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/13 20:09:30 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parsing_heredoc(char **argv)
{
	char	*store;
	char	*temp;
	char	*temp2;

	store = "";
	while (1)
	{
		temp = get_next_line(0);
		if (!ft_strncmp(argv[2], temp, ft_strlen(argv[2])))
			break ;
		temp2 = ft_strjoin(store, temp);
		if (store[0] != '\0')
			free(store);
		store = temp2;
		free(temp);
	}
	free(temp);
	return (store);
}

void	exec_here_doc2(t_info **info, pid_t here_pid, int here_fd[2], int fd[2])
{
	close(here_fd[1]);
	dup2(here_fd[0], 0);
	dup2(fd[1], 1);
	waitpid(here_pid, NULL, 0);
	execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
}

void	exec_here_doc(t_info **info, char **argv, int fd[2])
{
	char	*temp;
	int		here_fd[2];
	pid_t	here_pid;

	if (pipe(here_fd) == -1)
	{
		perror("Error : pipe function");
		exit(1);
	}
	here_pid = fork();
	if (here_pid == 0)
	{
		close(here_fd[0]);
		temp = parsing_heredoc(argv);
		write(here_fd[1], temp, ft_strlen(temp));
		exit(0);
	}
	else if (here_pid > 0)
		exec_here_doc2(info, here_pid, here_fd, fd);
	else
	{
		perror("Error : fork function");
		exit(1);
	}
}

void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		in_fd;

	if (pid == 0 && (*info)->is_heredoc == 1 && (*info)->i == 1)
		exec_here_doc(info, argv, fd);
	else if (pid == 0 && (*info)->i == 0)
	{
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
		o = open(argv[(*info)->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (o == -1)
		{
			perror("Error : open file Error");
			exit(1);
		}
		temp = read_fd(fd);
		write(o, temp, ft_strlen(temp));
		if (temp && temp[0] != '\0')
			free(temp);
	}
	if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}
