/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:09:25 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/20 14:46:42 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	(*info)->argc = argc;
}

void	perror_exit(char *str)
{
	perror(str);
	exit(1);
}

void	cmd_error(int sign)
{
	if (sign == 0)
		write(2, "Error : Invalid command!\n", 25);
}

int	check_file(t_info **info, char **argv)
{
	if ((*info)->argc != 5)
	{
		write(2, "Error : check your arguments\n", 32);
		exit(1);
	}
	if (access(argv[1], R_OK))
		perror_exit("Error :Check input file");
	return (1);
}
