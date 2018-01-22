/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:59:41 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 10:15:01 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*str;
	size_t	n;

	n = 0;
	if (size == 0)
		return (NULL);
	if ((str = malloc(size + 1)) == NULL)
		return (NULL);
	while (n <= size)
		str[n++] = '\0';
	return (str);
}
