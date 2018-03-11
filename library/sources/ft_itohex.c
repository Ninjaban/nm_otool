/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:31:08 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/09 11:36:38 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_itohex_retenu(long int *res, unsigned int n, long int nbr,
								unsigned int size)
{
	static unsigned int		ret = 0;

	if (n == size - 1 && nbr < 0)
	{
		if (*res < 15)
			*res += 1;
		else
		{
			ret = 1;
			*res = 0;
		}
	}
	else if (ret > 0)
	{
		ret = 0;
		if (*res < 15)
			*res += 1;
		else
		{
			ret = 1;
			*res = 0;
		}
	}
}

int			ft_itohex(long int nbr, char *bytes, unsigned int size)
{
	long int		res;
	unsigned int	n;

	if (!size || !bytes)
		return (0);
	n = 0;
	while (n < size)
		bytes[n++] = (nbr >= 0) ? '0' : 'f';
	n = size - 1;
	while (nbr)
	{
		res = (nbr > 0) ? nbr % 16 : 15 + (nbr % 16);
		ft_itohex_retenu(&res, n, nbr, size);
		bytes[n] = (res < 10) ? res + '0' : res - 10 + 'a';
		nbr = nbr / 16;
		if (n == 0)
			break ;
		n = n - 1;
	}
	return (size);
}
