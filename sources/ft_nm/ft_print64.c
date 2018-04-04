/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:16:38 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/29 09:13:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

static t_bool	ft_types_push_back(t_types **types, uint32_t n_sect, char type)
{
	t_types		*tmp;

	tmp = *types;
	if (*types)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = malloc(sizeof(t_types *))))
			return (FALSE);
		tmp = tmp->next;
	}
	else
	{
		if (!(*types = malloc(sizeof(t_types *))))
			return (FALSE);
		tmp = *types;
	}
	tmp->n_sect = n_sect;
	tmp->type = type;
	tmp->next = NULL;
	return (TRUE);
}

static t_bool	ft_get_type_sectname(char *name, uint32_t n_sect,
									t_types **types)
{
	char	type;

	if (!ft_strcmp(name, SECT_DATA))
		type = 'D';
	else if (!ft_strcmp(name, SECT_BSS))
		type = 'B';
	else if (!ft_strcmp(name, SECT_TEXT))
		type = 'T';
	else
		type = 'S';
	return (ft_types_push_back(types, n_sect, type));
}

static t_bool	ft_get_type_nsect(struct load_command *lc, uint32_t *n_sect,
									t_types **types)
{
	struct section_64			*sec;
	struct segment_command_64	*seg;
	uint32_t					n;

	n = 0;
	seg = (struct segment_command_64 *)lc;
	if (!(CHECK_ADDR(seg, sizeof(struct segment_command *))))
		return (FALSE);
	sec = (struct section_64 *)(seg + 1);
	while (n < seg->nsects)
	{
		if (!(CHECK_ADDR(sec, sizeof(struct section *))))
			return (FALSE);
		if (!ft_get_type_sectname(sec->sectname, *n_sect, types))
			return (FALSE);
		*n_sect = *n_sect + 1;
		sec = sec + 1;
		n = n + 1;
	}
	return (TRUE);
}

extern t_bool	ft_get_type64(struct load_command *lc, t_types **types)
{
	uint32_t			n;
	uint32_t			n_sect;

	n = 0;
	n_sect = 1;
	*types = NULL;
	while (n < ((struct mach_header_64 *)((void *)lc -
			sizeof(struct mach_header_64 *)))->ncmds)
	{
		if (!(CHECK_ADDR(lc, sizeof(struct load_command *))))
			return (ft_get_type_free(*types));
		if (lc->cmd == LC_SEGMENT_64 && !ft_get_type_nsect(lc, &n_sect, types))
			return (ft_get_type_free(*types));
		lc = (void *)lc + lc->cmdsize;
		n = n + 1;
	}
	return (TRUE);
}
