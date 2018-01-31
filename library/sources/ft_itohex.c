/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:31:08 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/31 12:43:16 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int			ft_itohex(int nbr, char *bytes, unsigned int size)
{
	int				res;
	unsigned int	n;

	if (!size || !bytes)
		return (0);
	n = 0;
	while (n < size)
		bytes[n++] = (nbr > 0) ? '0' : 'f';
	n = size - 1;
	while (nbr)
	{
		res = (nbr > 0) ? nbr % 16 : 15 + (nbr % 16);
		if (n == size - 1 && nbr < 0)
			res += 1;
		bytes[n] = (res < 10) ? res + '0' : res - 10 + 'a';
		nbr = nbr / 16;
		if (n == 0)
			break ;
		n = n - 1;
	}
	return (size);
}
