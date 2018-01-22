/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:37:35 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 14:30:49 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_revstr(char *str)
{
	char	*rev;
	int		n;
	int		i;

	n = 0;
	i = ft_strlen(str) - 1;
	if ((rev = malloc(ft_strlen(str) + 1)) == NULL)
		return (NULL);
	while (i >= 0)
		rev[n++] = str[i--];
	rev[n] = '\0';
	free(str);
	return (rev);
}
