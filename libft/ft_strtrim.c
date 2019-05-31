/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:14:41 by mpas              #+#    #+#             */
/*   Updated: 2018/10/14 00:23:00 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
			c == '\r')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*b;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] != '\0' && ft_isspace(s[start]))
		start++;
	if (s[start] == '\0')
		return (ft_strdup(s + start));
	while (s[end - 1] && ft_isspace(s[end - 1]))
		end--;
	b = ft_strsub(s, start, end - start);
	if (b)
		return (b);
	return (0);
}
