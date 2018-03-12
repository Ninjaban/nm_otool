/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:50:12 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/12 17:22:34 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdlib.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

static void			ft_get_order_swap(uint32_t *order, uint32_t *n)
{
	uint32_t		tmp;

	tmp = order[*n];
	order[*n] = order[*n + 1];
	order[*n + 1] = tmp;
	*n = 0;
}

static uint32_t		*ft_get_order(uint32_t nsyms, char *stringtable,
									struct nlist *list)
{
	uint32_t		*order;
	uint32_t		n;

	if (!(order = malloc(sizeof(uint32_t) * nsyms)))
		return (NULL);
	n = 0;
	while (++n <= nsyms)
		order[n - 1] = n - 1;
	n = 0;
	while (n < nsyms)
	{
		if (!(stringtable + list[order[n]].n_un.n_strx) || (n + 1 < nsyms &&
					!(stringtable + list[order[n + 1]].n_un.n_strx)))
		{
			free(order);
			return (NULL);
		}
		if (n + 1 < nsyms && ft_strcmp(
				stringtable + list[order[n]].n_un.n_strx,
				stringtable + list[order[n + 1]].n_un.n_strx) > 0)
			ft_get_order_swap(order, &n);
		else
			n = n + 1;
	}
	return (order);
}

static void			ft_display(char *stringtable, struct nlist *list,
								uint32_t index, struct load_command *lc)
{
	char		bytes[12];
	char		c;

	c = ' ';
	if ((list[index].n_type < N_SECT && list[index].n_sect != NO_SECT) ||
		!ft_strlen(stringtable + list[index].n_un.n_strx) ||
		(list[index].n_type != 1 && list[index].n_value == 0))
		return ;
	if (list[index].n_type >= N_SECT)
	{
		if ((c = ft_get_type(list[index].n_sect, list[index].n_type, lc,
							 ft_get_type32)) == ' ')
			return ;
	}
	else if (list[index].n_sect == NO_SECT)
		c = 'U';
	ft_memset(bytes, ' ', 11);
	bytes[11] = '\0';
	if (list[index].n_type != 1)
		ft_itohex(list[index].n_value, bytes, 8);
	bytes[9] = c;
	ft_putstr(bytes);
	ft_putstr(stringtable + list[index].n_un.n_strx);
	ft_putchar('\n');
}

static t_bool		ft_print(struct symtab_command *sym, void *ptr, struct load_command *lc)
{
	char			*stringtable;
	struct nlist	*list;
	uint32_t		*order;
	uint32_t		n;

	list = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	if (!(order = ft_get_order(sym->nsyms, stringtable, list)))
		return (FALSE);
	n = 0;
	while (n < sym->nsyms)
	{
		if (ft_strcmp(stringtable + list[order[n]].n_un.n_strx,
					"radr://5614542"))
			ft_display(stringtable, list, order[n], lc);
		n = n + 1;
	}
	free(order);
	return (TRUE);
}

extern t_bool		ft_header_32(t_buffer file)
{
	struct load_command		*lc;
	struct mach_header		*header;
	struct symtab_command	*sym;
	uint32_t				n;

	header = (struct mach_header *)file.bytes;
	lc = (void *)file.bytes + sizeof(*header);
	n = 0;
	while (n < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (((struct nlist_64 *)(file.bytes +
					sym->symoff))[sym->nsyms - 1].n_un.n_strx >= sym->strsize)
				return (FALSE);
			if (!ft_print(sym, file.bytes, (void *)file.bytes + sizeof(*header)))
				return (FALSE);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		n = n + 1;
	}
	return (TRUE);
}
