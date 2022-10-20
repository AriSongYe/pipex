/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:15:33 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/20 14:48:04 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**valid_cmd(char *cmd, char **path)
{
	char	**cmd_info;
	char	*temp;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	cmd_info = ft_split(cmd, ' ');
	if (!access(cmd_info[0], F_OK))
		return (cmd_info);
	while (path[i])
	{
		temp = join_path(cmd_info[0], path[i]);
		if (!access (temp, F_OK))
		{
			sign = 1;
			break ;
		}
		if (path [1 + i++] != NULL)
			free(temp);
	}
	free(cmd_info[0]);
	cmd_info[0] = temp;
	cmd_error(sign);
	return (cmd_info);
}

void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		in_fd;

	if (pid == 0 && (*info)->i == 0)
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
		o = open(argv[(*info)->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
