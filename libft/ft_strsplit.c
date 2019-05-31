/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:21:32 by mpas              #+#    #+#             */
/*   Updated: 2018/10/03 00:13:44 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_length(char const *str, char c)
{
	size_t	kolichestvo;

	kolichestvo = 0;
	if (!str)
		return (0);
	while (str[kolichestvo] != c && str[kolichestvo])
		kolichestvo++;
	return (kolichestvo);
}

static size_t	ft_kol(char const *s, char c)
{
	size_t	kolichestvo;

	kolichestvo = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			kolichestvo++;
		s++;
	}
	return (kolichestvo);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		slova;
	char		**matrix;

	i = 0;
	if (!s || !c)
		return ((void *)0);
	slova = ft_kol(s, c);
	if (!(matrix = (char **)malloc(sizeof(char *) * (slova + 1))))
		return (NULL);
	while (i < slova)
	{
		while (*s == c && *s)
			s++;
		matrix[i] = (char *)malloc(sizeof(char) * (ft_length(s, c) + 1));
		j = 0;
		while (*s != c && *s)
			matrix[i][j++] = *s++;
		matrix[i][j] = '\0';
		i++;
	}
	matrix[i] = 0;
	return (matrix);
}
