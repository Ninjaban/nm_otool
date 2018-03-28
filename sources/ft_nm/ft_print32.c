/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:16:38 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/21 10:20:50 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

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

static char			ft_get_type_nsect(uint32_t n_sect, struct load_command *lc,
										uint32_t *nb_n_sect)
{
	struct section			*sec;
	struct segment_command	*seg;
	uint32_t				n;

	n = 0;
	seg = (struct segment_command *)lc;
	if (!(CHECK_ADDR(seg, sizeof(struct segment_command *))))
		return ('?');
	sec = (struct section *)(seg + 1);
	while (n < seg->nsects)
	{
		if (!(CHECK_ADDR(sec, sizeof(struct section *))))
			return ('?');
		if (*nb_n_sect == n_sect)
			return (ft_get_type_sectname(sec->sectname));
		*nb_n_sect = *nb_n_sect + 1;
		sec = sec + 1;
		n = n + 1;
	}
	return ('?');
}

extern char			ft_get_type32(uint32_t n_sect, struct load_command *lc)
{
	struct load_command *tmp;
	uint32_t			nb_n_sect;
	uint32_t			n;
	char				c;

	tmp = lc;
	nb_n_sect = 1;
	n = 0;
	c = '?';
	while (n < ((struct mach_header *)((void *)lc -
			sizeof(struct mach_header *)))->ncmds)
	{
		if (!(CHECK_ADDR(tmp, sizeof(struct load_command *))))
			return ('S');
		if (tmp->cmd == LC_SEGMENT &&
				(c = ft_get_type_nsect(n_sect, tmp, &nb_n_sect)) != '?')
			return (c);
		tmp = (void *)tmp + tmp->cmdsize;
		n = n + 1;
	}
	return ((c == '?') ? 'S' : c);
}
