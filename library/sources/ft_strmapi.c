/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:38:37 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:56:02 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	n;

	n = -1;
	if (s == NULL)
		return (NULL);
	if ((str = malloc(ft_strlen((char *)s) + 1)) == NULL)
		return (NULL);
	while (s[++n])
		str[n] = f(n, s[n]);
	str[n] = '\0';
	return (str);
}
