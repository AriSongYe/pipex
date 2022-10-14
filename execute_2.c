/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:28:31 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/14 16:01:44 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
