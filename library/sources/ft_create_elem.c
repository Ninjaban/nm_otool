/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 09:28:16 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/16 09:14:20 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_lst		*ft_create_elem(void *data)
{
	t_lst	*new_elem;

	if ((new_elem = malloc(sizeof(t_lst))) == NULL)
		return (NULL);
	new_elem->next = NULL;
	new_elem->data = data;
	return (new_elem);
}
