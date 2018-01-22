/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 09:39:23 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/06 09:40:19 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_list_push_back(t_lst **begin_list, void *data)
{
	t_lst	*new_elem;
	t_lst	*elem;

	if (!begin_list || !data)
		return ;
	if ((new_elem = ft_create_elem(data)) == NULL)
		return ;
	elem = *begin_list;
	if (elem == NULL)
		*begin_list = new_elem;
	else
	{
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new_elem;
	}
}
