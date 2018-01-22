/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 11:17:22 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/09 11:32:38 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_lst **begin_list)
{
	t_lst	*last;
	t_lst	*next;
	t_lst	*tmp;

	if (begin_list && *begin_list)
	{
		last = *begin_list;
		if (last->next != NULL)
		{
			next = last->next;
			last->next = NULL;
			while (next->next != NULL)
			{
				tmp = next->next;
				next->next = last;
				last = next;
				next = tmp;
			}
		}
	}
}
