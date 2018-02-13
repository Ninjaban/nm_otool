/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:46:53 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/13 10:13:33 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdlib.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

static uint32_t		*ft_get_order(uint32_t nsyms, char *stringtable,
									struct nlist_64 *list)
{
	uint32_t		*order;
	uint32_t		tmp;
	int				n;

	if (!(order = malloc(sizeof(uint32_t) * nsyms)))
		return (NULL);
	n = -1;
	while (++n < (int)nsyms)
		order[n] = (uint32_t)n;
	n = 0;
	while (n < (int)nsyms)
	{
		if (!(stringtable + list[order[n]].n_un.n_strx) || !(stringtable + list[order[n + 1]].n_un.n_strx))
		{
			free(order);
			return (NULL);
		}
		if (n + 1 < (int)nsyms && ft_strcmp(
				stringtable + list[order[n]].n_un.n_strx,
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

static void			ft_display(char *stringtable, struct nlist_64 *list,
								  uint32_t *order, uint32_t n)
{
	char		bytes[20];
	char		c;

	c = ' ';
	ft_putstr("DEBUG 3\n");
	if (list[order[n]].n_type >= N_SECT)
		c = ft_nsect_decription(list[order[n]].n_sect, list[order[n]].n_type);
	else if (list[order[n]].n_sect == NO_SECT)
		c = 'U';
	ft_memset(bytes, ' ', 19);
	bytes[19] = '\0';
	if (list[order[n]].n_type != 1)
		ft_itohex(list[order[n]].n_value, bytes, 16);
	bytes[17] = c;
	ft_putstr(bytes);
	ft_putstr(stringtable + list[order[n]].n_un.n_strx);
	ft_putchar('\n');
}

static t_bool		ft_print(uint32_t nsyms, int symoff, int stroff, void *ptr)
{
	char			*stringtable;
	struct nlist_64	*list;
	uint32_t		*order;
	uint32_t		n;

	list = ptr + symoff;
	stringtable = ptr + stroff;
	ft_putstr("DEBUG 2\n");
	if (!(order = ft_get_order(nsyms, stringtable, list)))
		return (FALSE);
	n = 0;
	while (n < nsyms)
	{
		if (ft_strcmp(stringtable + list[order[n]].n_un.n_strx,
					  "radr://5614542"))
			ft_display(stringtable, list, order, n);
		n = n + 1;
	}
	free(order);
	return (TRUE);
}

extern void			ft_header_64(t_buffer file)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	struct symtab_command	*sym;
	uint32_t				n;

	header = (struct mach_header_64 *)file.bytes;
	lc = (void *)file.bytes + sizeof(*header);
	n = 0;
	ft_putstr("DEBUG 1\n");
	while (n < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (!ft_print(sym->nsyms, sym->symoff, sym->stroff, file.bytes))
				ft_putstr_fd("Une erreur est survenue.\n", 2);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		n = n + 1;
	}
}