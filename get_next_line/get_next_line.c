/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:15:59 by yecsong           #+#    #+#             */
/*   Updated: 2022/10/12 15:00:32 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *store, int *end);
char	*ft_mystrjoin(char *s1, char *s2);
int		ft_mystrchr(const char *s, int *end);

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	char		*temp;
	int			end;

	end = 0;
	temp = read_line(fd, store, &end);
	if (!temp || end == 0)
	{
		free(temp);
		store = NULL;
		return (NULL);
	}
	line = ft_mystrdup(temp, end);
	store = ft_mystrdup(temp + end, ft_mystrlen (temp + end));
	free(temp);
	return (line);
}

char	*read_line(int fd, char *store, int *end)
{
	char	*buff;
	int		n;

	if (store && ft_mystrchr(store, end))
		return (store);
	if (store)
		*end = ft_mystrlen(store);
	buff = (char *)malloc(sizeof(char) * (10 + 1));
	while (1)
	{
		n = read(fd, buff, 10);
		if (n == 0 || n == -1)
			break ;
		buff[n] = '\0';
		store = ft_mystrjoin(store, buff);
		if (!store || ft_mystrchr(store, end))
			break ;
		*end += n;
	}
	free(buff);
	return (store);
}

char	*ft_mystrjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	s1_len = 0;
	if (s1)
		s1_len = ft_mystrlen(s1);
	s2_len = ft_mystrlen(s2);
	ptr = (char *)malloc(sizeof(char) *(s1_len + s2_len + 1));
	if (!ptr)
		return (NULL);
	ft_mystrlcpy(ptr, s1, s1_len + 1);
	ft_mystrlcpy(ptr + s1_len, s2, s2_len + 1);
	free(s1);
	return (ptr);
}

int	ft_mystrchr(const char *s, int *end)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			*end = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}
