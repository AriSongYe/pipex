/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:17:06 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/14 15:57:56 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	check_file(t_info **info, char **argv)
{
	if ((*info)->argc < 5)
	{
		write(2, "Error : arguments is not enough!\n", 32);
		exit(1);
	}
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		(*info)->is_heredoc = 1;
		if ((*info)->is_heredoc == 1 && (*info)->argc < 6)
		{
			write(2, "Error : arguments is not enough!\n", 32);
			exit(1);
		}
		return (0);
	}
	if (access(argv[1], R_OK))
		perror_exit("Error :Check input file");
	return (1);
}
