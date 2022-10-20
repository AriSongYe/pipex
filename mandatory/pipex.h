/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:46:09 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/20 14:46:37 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_info
{
	char	**path;
	char	**cmd_info;
	int		i;
	int		argc;
}	t_info;

char	**valid_cmd(char *cmd, char **path);
char	**parsing_path(char **envp);
char	*join_path(char *cmd, char *path);
char	*read_fd(int fd);
void	pipe_line(t_info **info, char **argv);
void	parent_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	free_dptr(char **ptr);
void	cmd_error(int sign);
void	perror_exit(char *str);
void	init_info(int argc, t_info **info);
int		check_file(t_info **info, char **argv);

#endif
