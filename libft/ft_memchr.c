/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 22:50:47 by mpas              #+#    #+#             */
/*   Updated: 2018/09/21 22:51:44 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	symb;
	size_t			i;

	i = 0;
	string = (unsigned char *)s;
	symb = (unsigned char)c;
	while (n)
	{
		if (string[i] == symb)
		{
			return (string + i);
		}
		i++;
		n--;
	}
	return (NULL);
}
