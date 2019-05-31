/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 23:39:35 by mpas              #+#    #+#             */
/*   Updated: 2018/10/14 00:50:04 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lsize(t_list *begin)
{
	int		size;
	t_list	*current;

	size = 0;
	current = begin;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
