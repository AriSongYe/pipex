/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:06:10 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/13 19:42:47 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(argc, &info);
	check_file(&info, argv);
	if (info->is_heredoc == 1)
		info->i = 1;
	info->path = parsing_path(envp);
	while (info->i < argc - 3)
	{
		exec_cmd(&info, argv);
		info->i++;
		free_dptr(info->cmd_info);
	}
}
