/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:02:33 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:59:13 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((str = malloc(ft_strlen((char *)s1) +
						ft_strlen((char *)s2) + 1)) == NULL)
		return (NULL);
	while (s1[i])
		str[n++] = s1[i++];
	i = 0;
	while (s2[i])
		str[n++] = s2[i++];
	str[n] = '\0';
	return (str);
}
