/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:06:10 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/19 19:28:37 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(argc, &info);
	check_file(&info, argv);
	if (info->is_heredoc == 1)
	{
		create_temp_file(argv);
		info->i = 1;
	}
	info->path = parsing_path(envp);
	while (info->i < argc - 3)
	{
		info->cmd_info = valid_cmd(argv[info->i + 2], info->path);
		pipe_line(&info, argv);
		info->i++;
		free_dptr(info->cmd_info);
	}
	if (info->is_heredoc == 1)
		unlink("/tmp/temp_pipex");
}
