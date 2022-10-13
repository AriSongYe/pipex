/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:19:15 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/13 19:19:50 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parsing_path(char **envp)
{
	char	**path;
	char	*temp;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			break ;
		(*envp)++;
	}
	temp = ft_strdup(*envp + 5);
	path = ft_split(temp, ':');
	free(temp);
	return (path);
}

char	*join_path(char *cmd, char *path)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin("/", cmd);
	temp2 = temp;
	temp = ft_strjoin(path, temp2);
	free(temp2);
	return (temp);
}

void	cmd_error(int sign)
{
	if (sign == 0)
		write(2, "Error : Invalid command!\n", 25);
}

char	**valid_cmd(char *cmd, char **path)
{
	char	**cmd_info;
	char	*temp;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	cmd_info = ft_split(cmd, ' ');
	while (path[i])
	{
		temp = join_path(cmd_info[0], path[i]);
		if (!access (temp, F_OK))
		{
			sign = 1;
			break ;
		}
		if (path [i + 1] != NULL)
			free(temp);
		i++;
	}
	free(cmd_info[0]);
	cmd_info[0] = temp;
	cmd_error(sign);
	return (cmd_info);
}
