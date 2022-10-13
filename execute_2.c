/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:28:31 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/13 19:31:02 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_line(t_info **info, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("Error : pipe function");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork function");
		exit(1);
	}
	child_exec(info, argv, fd, pid);
	parent_exec(info, argv, fd, pid);
}

int	exec_cmd(t_info **info, char **argv)
{
	(*info)->cmd_info = valid_cmd(argv[(*info)->i + 2], (*info)->path);
	pipe_line(info, argv);
	return (1);
}
