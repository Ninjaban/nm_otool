/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:52:51 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/12 15:22:51 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_reverse_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	if (c >= 'A' && c <= 'Z')
		return (c - 'Z' + 'a');
	return (c);
}

int			ft_strcmp_case(const char *s1, const char *s2)
{
	int	n;

	n = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[n] == s2[n] || s1[n] == ft_reverse_char(s2[n])) && s1[n] &&
			s2[n])
		n = n + 1;
	return ((unsigned char)s1[n] - (unsigned char)s2[n]);
}
