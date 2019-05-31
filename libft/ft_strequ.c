/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:05:16 by mpas              #+#    #+#             */
/*   Updated: 2018/09/24 23:12:11 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	const unsigned char *p1 = (const unsigned char *)s1;
	const unsigned char *p2 = (const unsigned char *)s2;

	if (!p1 || !p2)
		return (0);
	while (*p1 == *p2)
	{
		if (*p1 == '\0' && *p2 == '\0')
			return (1);
		p1++;
		p2++;
	}
	return (0);
}
