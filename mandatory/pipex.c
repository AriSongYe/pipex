/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:44:22 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/19 20:20:11 by yecsong          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(argc, &info);
	check_file(&info, argv);
	info->path = parsing_path(envp);
	while (info->i < argc - 3)
	{
		info->cmd_info = valid_cmd(argv[info->i + 2], info->path);
		pipe_line(&info, argv);
		info->i++;
		free_dptr(info->cmd_info);
	}
}
