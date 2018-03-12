/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:46:53 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/12 16:43:39 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <printf.h>

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
									struct nlist_64 *list)
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

static char			ft_get_type_sectname(char *name)
{
	if (!ft_strcmp(name, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(name, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(name, SECT_TEXT))
		return ('T');
	else
		return ('S');
}

static char			ft_get_type_nsect(uint32_t n_sect, struct load_command *lc, uint32_t *nb_n_sect)
{
	struct section_64			*sec;
	struct segment_command_64	*seg;
	uint32_t					n;

	n = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + 1);
	while (n < seg->nsects)
	{
		if (*nb_n_sect == n_sect)
			return (ft_get_type_sectname(sec->sectname));

		*nb_n_sect = *nb_n_sect + 1;
		sec = sec + 1;
		n = n + 1;
	}
	return ('?');
}

static char			ft_get_type_lc(uint32_t n_sect, struct load_command *lc)
{
	struct load_command *tmp;
	uint32_t			nb_n_sect;
	uint32_t			n;
	char				c;

	tmp = lc;
	nb_n_sect = 1;
	n = 0;
	c = '?';
	while (n < ((struct mach_header_64 *)((void *)lc - sizeof(struct mach_header_64 *)))->ncmds)
	{
		if (tmp->cmd == LC_SEGMENT_64 && (c = ft_get_type_nsect(n_sect, tmp, &nb_n_sect)) != '?')
			return (c);
		tmp = (void *)tmp + tmp->cmdsize;
		n = n + 1;
	}
	return ((c == '?') ? 'S' : c);
}

static void			ft_display(char *stringtable, struct nlist_64 *list,
								uint32_t index, struct load_command *lc)
{
	char		bytes[20];
	char		c;

	c = ' ';
	if ((list[index].n_type < N_SECT && list[index].n_sect != NO_SECT) ||
			!ft_strlen(stringtable + list[index].n_un.n_strx) ||
			(list[index].n_type != 1 && list[index].n_value == 0))
		return ;
	if (list[index].n_type >= N_SECT)
	{
		if ((c = ft_get_type(list[index].n_sect, list[index].n_type, lc, ft_get_type_lc)) == ' ')
			return ;
	}
	else if (list[index].n_sect == NO_SECT)
		c = 'U';
	ft_memset(bytes, ' ', 19);
	bytes[19] = '\0';
	if (list[index].n_type != 1)
		ft_itohex(list[index].n_value, bytes, 16);
	bytes[17] = c;
	ft_putstr(bytes);
	ft_putstr(stringtable + list[index].n_un.n_strx);
	ft_putchar('\n');
}

static t_bool		ft_print(struct symtab_command *sym, void *ptr, struct load_command *lc)
{
	char			*stringtable;
	struct nlist_64	*list;
	uint32_t		*order;
	uint32_t		n;

	if (!(list = ptr + sym->symoff))
		return (FALSE);
	if (!(stringtable = ptr + sym->stroff))
		return (FALSE);
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

extern t_bool		ft_header_64(t_buffer file)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	struct symtab_command	*sym;
	uint32_t				n;

	if (!(header = (struct mach_header_64 *)file.bytes))
		return (FALSE);
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
