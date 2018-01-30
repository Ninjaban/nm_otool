//
// Created by Nathan on 30/01/18.
//

#include <stdlib.h>
#include "libft.h"
#include "types.h"

extern char			ft_nsect_decription(uint32_t n_sect, uint32_t n_type)
{
	if (n_sect == 1 && n_type == 14)
		return ('t');
	if (n_sect == 1 && n_type == 15)
		return ('T');
	if (n_sect == 9 && n_type == 14)
		return ('b');
	if (n_sect == 9 && n_type == 15)
		return ('B');
	if (n_sect == 11 && n_type == 14)
		return ('d');
	if (n_sect == 11 && n_type == 15)
		return ('D');
	if (n_sect == 12 && n_type == 14)
		return ('s');
	if (n_sect == 12 && n_type == 15)
		return ('S');
	return (0);
}

extern uint32_t		*ft_get_order(uint32_t nsyms, char *stringtable,
									 struct nlist_64 *list)
{
	uint32_t		*order;
	uint32_t		tmp;
	uint32_t		n;

	if (!(order = malloc(sizeof(uint32_t) * nsyms)))
		return (NULL);
	n = 0;
	while (n < nsyms)
		order[n] = n++;
	n = 0;
	while (n < nsyms)
	{
		if (n + 1 < nsyms && ft_strcmp(stringtable + list[order[n]].n_un.n_strx,
							stringtable + list[order[n + 1]].n_un.n_strx) >= 0)
		{
			tmp = order[n];
			order[n] = order[n + 1];
			order[n + 1] = tmp;
			n = 0;
		}
		else
			n = n + 1;
	}
	return (order);
}
