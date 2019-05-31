/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:12:29 by mpas              #+#    #+#             */
/*   Updated: 2018/09/24 23:12:42 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*constr;

	constr = NULL;
	if (!s1 || !s2 ||
			!(constr = (ft_strnew(ft_strlen(s1) + ft_strlen(s2) - 1))))
		return (NULL);
	constr = ft_strcpy(constr, s1);
	constr = ft_strcat(constr, s2);
	return (constr);
}
