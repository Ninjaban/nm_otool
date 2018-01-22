/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 09:23:39 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/12 09:53:21 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_swap(t_lst **begin, t_lst *node1, t_lst *node2)
{
	t_lst	*tmp;

	if (!begin || !(*begin) || !node1 || !node2)
		return ;
	node1->next = node2->next;
	node2->next = node1;
	if (*begin == node1)
	{
		*begin = node2;
		return ;
	}
	tmp = *begin;
	while (tmp->next && tmp->next != node1)
		tmp = tmp->next;
	if (tmp->next)
		tmp->next = node2;
}

void	ft_list_sort(t_lst **begin, int (*f)(const char *, const char *))
{
	t_lst	*tmp;
	char	modif;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	modif = 0;
	while (tmp->next)
	{
		if (f(tmp->data, tmp->next->data) > 0)
		{
			ft_list_swap(&(*begin), tmp, tmp->next);
			modif = 1;
		}
		else
			tmp = tmp->next;
		if (!tmp->next && modif == 1)
		{
			tmp = *begin;
			modif = 0;
		}
	}
}
