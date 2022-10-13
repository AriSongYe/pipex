/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:00:29 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/12 14:58:52 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

char	*read_line(int fd, char *store, int *end);
char	*ft_mystrjoin(char *s1, char *s2);
char	*ft_mystrdup(const char *s1, int size);
size_t	ft_mystrlcpy(char *dst, const char *src, size_t dstsize);
int		ft_mystrchr(const char *s, int *end);
int		ft_mystrlen(const char *s);
char	*get_next_line(int fd);

#endif
