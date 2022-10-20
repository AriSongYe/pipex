/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:31:09 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/19 19:28:47 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*read_fd(int fd)
{
	char	*temp;
	char	*temp2;
	char	*store;

	store = "";
	while (1)
	{
		temp = get_next_line(fd);
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

void	free_dptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	create_temp_file(char **argv)
{
	int		temp_fd;
	char	*temp;

	temp_fd = open("/tmp/temp_pipex", O_CREAT | O_RDWR | O_TRUNC, 0644);
	temp = parsing_heredoc(argv);
	write(temp_fd, temp, ft_strlen(temp));
	if (temp[0] != '\0')
		free(temp);
	close(temp_fd);
}
