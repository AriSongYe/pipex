/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:31:09 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/14 15:36:32 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_fd(int fd[2])
{
	char	*temp;
	char	*temp2;
	char	*store;

	store = "";
	while (1)
	{
		temp = get_next_line(fd[0]);
		if (!temp)
			break ;
		temp2 = ft_strjoin(store, temp);
		if (store[0] != '\0')
			free(store);
		store = temp2;
		free(temp);
	}
	return (store);
}

void	init_info(int argc, t_info **info)
{
	(*info)->i = 0;
	(*info)->path = NULL;
	(*info)->cmd_info = NULL;
	(*info)->is_heredoc = 0;
	(*info)->argc = argc;
}

void	perror_exit(char *str)
{
	perror(str);
	exit(1);
}
