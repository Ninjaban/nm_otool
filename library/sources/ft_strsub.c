/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:58:09 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:58:10 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;

	n = 0;
	if (s == NULL)
		return (NULL);
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	while (n < len)
	{
		str[n] = s[start + n];
		n = n + 1;
	}
	str[n] = '\0';
	return (str);
}
