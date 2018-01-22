/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 10:14:23 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/09 11:32:14 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_list_push_params(int ac, char **av)
{
	int		n;
	t_lst	*new;

	n = 1;
	new = NULL;
	if (ac > 1)
		new = ft_create_elem(av[n++]);
	while (n < ac)
	{
		new->next = ft_create_elem(av[n++]);
		new = new->next;
	}
	if (new != NULL)
		new->next = ft_create_elem(av[0]);
	else
		new = ft_create_elem(av[0]);
	return (new);
}
