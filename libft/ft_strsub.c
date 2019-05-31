/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:10:33 by mpas              #+#    #+#             */
/*   Updated: 2018/09/24 23:13:52 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*b;
	const char	*src;
	size_t		i;

	if (!s)
		return (NULL);
	b = ft_strnew(len);
	if (b == NULL)
		return (0);
	src = &s[start];
	i = 0;
	while (src[i] && i < len)
	{
		b[i] = src[i];
		i++;
	}
	while (i < len)
	{
		b[i] = '\0';
		i++;
	}
	return (b);
}
