/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:19:52 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/19 19:43:38 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_info
{
	char	**path;
	char	**cmd_info;
	int		is_heredoc;
	int		i;
	int		argc;
}	t_info;

char	**parsing_path(char **envp);
char	**valid_cmd(char *cmd, char **path);
char	*join_path(char *cmd, char *path);
char	*parsing_heredoc(char **argv);
char	*read_fd(int fd);
void	free_dptr(char **ptr);
void	cmd_error(int sign);
void	exec_here_doc(t_info **info, char **argv, int fd[2]);
void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	parent_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	pipe_line(t_info **info, char **argv);
void	init_info(int argc, t_info **info);
void	perror_exit(char *str);
void	create_temp_file(char **argv);
int		check_file(t_info **info, char **argv);

#endif
