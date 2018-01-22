/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:36:29 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/12 15:13:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *src)
{
	int		n;

	n = 0;
	if (!str || !src)
		return (NULL);
	if (!src[0])
		return ((char *)str);
	while (str[n])
	{
		while (str[n] && str[n] != src[0])
			n = n + 1;
		if (ft_strncmp(str + n, src, ft_strlen((char *)src) - 1) == 0)
			return ((char *)(str + n));
		if (str[n])
			n = n + 1;
	}
	return (NULL);
}
