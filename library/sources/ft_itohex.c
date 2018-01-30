//
// Created by Nathan on 30/01/18.
//

int			ft_itohex(int nbr, char *bytes, unsigned int size)
{
	int				res;
	unsigned int	n;

	if (!size || !bytes)
		return (0);
	n = 0;
	while (n < size)
		bytes[n++] = '0';
	n = size - 1;
	while (nbr)
	{
		res = (nbr > 0) ? nbr % 16 : (nbr % 16) * -1;
		bytes[n] = (res < 10) ? res : res - 10 + 'a';
		nbr = nbr / 16;
		if (n == 0)
			break;
		n = n - 1;
	}
	return (size);
}
