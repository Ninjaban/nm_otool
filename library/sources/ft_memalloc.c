/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:58:28 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:14:35 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char	*ptr;

	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	while (--size != 0)
		ptr[size] = 0;
	ptr[0] = 0;
	return ((void *)ptr);
}
