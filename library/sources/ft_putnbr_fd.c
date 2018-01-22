/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:53:55 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/09 10:39:15 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_putnbr_fd(int nbr, int fd)
{
	unsigned long int	rev;
	char				c;

	if (nbr == 0)
		ft_putstr_fd("0", fd);
	else if (nbr == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (nbr < 0)
			ft_putchar_fd('-', fd);
		rev = ABS(nbr);
		rev = ft_revnbr(rev);
		while (rev != 1)
		{
			c = rev % 10 + '0';
			rev = rev / 10;
			ft_putchar_fd(c, fd);
		}
	}
}
