/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:19:52 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/13 20:03:38 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_info
{
	char	**path;
	char	**cmd_info;
	char	*out_char;
	int		is_heredoc;
	int		i;
	int		argc;
}	t_info;

# define READ 0
# define WRITE 1

void	free_dptr(char **ptr);
int		valid_file(t_info **info, char **argv);
int		check_file(t_info **info, char **argv);
char	**parsing_path(char **envp);
char	*join_path(char *cmd, char *path);
void	cmd_error(int sign);
char	**valid_cmd(char *cmd, char **path);
char	*parsing_heredoc(char **argv);
void	exec_here_doc(t_info **info, char **argv, int fd[2]);
void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	parent_exec(t_info **info, char **argv, int fd[2], pid_t pid);
void	pipe_line(t_info **info, char **argv);
int		exec_cmd(t_info **info, char **argv);
void	init_info(int argc, t_info **info);
char	*read_fd(int fd[2]);

#endif
