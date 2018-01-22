/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:12:04 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/12 15:14:05 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		n;

	if (!s)
		return (NULL);
	n = ft_strlen((char *)s);
	while (n >= 0 && s[n] != c)
		n = n - 1;
	if (n >= 0)
		return ((char *)(s + n));
	return (NULL);
}
