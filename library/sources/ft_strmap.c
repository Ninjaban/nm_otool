/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:31:45 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:55:29 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		n;

	n = -1;
	if (s == NULL)
		return (NULL);
	if ((str = malloc(ft_strlen((char *)s) + 1)) == NULL)
		return (NULL);
	while (s[++n])
		str[n] = f(s[n]);
	str[n] = '\0';
	return (str);
}
