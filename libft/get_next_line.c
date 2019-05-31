/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:08:21 by mpas              #+#    #+#             */
/*   Updated: 2019/03/15 14:10:50 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_n(char	const *s1, char	const *s2)
{
	char	*join;
	char	*temp;

	if (!s1 || !s2 ||
	((temp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == 0))
		return (NULL);
	join = temp;
	ft_strcpy(temp, s1);
	ft_strcat(temp, s2);
	return (join);
}

int		reading(const int fd, char **str)
{
	char	buf[BUFF_SIZE + 1];
	char	*temp;
	int		pos;

	if ((pos = read(fd, buf, BUFF_SIZE)) < 0)
		return (-1);
	buf[pos] = '\0';
	if (pos == 0)
		return (pos);
	temp = ft_strjoin_n(*str, buf);
	if (temp == NULL)
		return (-1);
	free(*str);
	*str = temp;
	return (pos);
}

int		magic_trick(int *res, char **str, char **buf)
{
	if (*res == 0)
	{
		if (((*str) = ft_strchr((*buf), '\0')) == (*buf))
			return (0);
	}
	else if (*res < 0)
		return (-1);
	else
		*str = ft_strchr((*buf), '\n');
	return (1);
}

void	norminette(char **str, char **buf)
{
	*str = ft_strdup((*str) + 1);
	free((*buf));
	*buf = *str;
}

int		get_next_line(const int fd, char **line)
{
	char		*str;
	int			res;
	static char	*buf = NULL;

	if (buf == NULL)
	{
		if ((buf = (char*)malloc(sizeof(char) + BUFF_SIZE)) == NULL)
			return (-1);
		ft_bzero(buf, sizeof(char));
	}
	str = ft_strchr(buf, '\n');
	while (str == NULL)
	{
		res = reading(fd, &buf);
		if (magic_trick(&res, &str, &buf) == 0)
			return (0);
		else if (magic_trick(&res, &str, &buf) == -1)
			return (-1);
	}
	*line = ft_strsub(buf, 0, str - buf);
	if (*line == NULL)
		return (-1);
	norminette(&str, &buf);
	return (1);
}
