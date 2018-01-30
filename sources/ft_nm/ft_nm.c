/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:20:59 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/29 16:18:30 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdlib.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

/*
** -- basic check
*/
typedef char	t__check_for_ft_nm_true[(TRUE == 1) ? 1 : -1];
typedef char	t__check_for_ft_nm_false[(FALSE == 0) ? 1 : -1];

static void			ft_display(char *stringtable, struct nlist_64 *list,
								uint32_t *order, uint32_t n)
{
	char		bytes[20];
	char		c;

	c = ' ';
	if (list[order[n]].n_type >= N_SECT)
		c = ft_nsect_decription(list[order[n]].n_sect, list[order[n]].n_type);
	else if (list[order[n]].n_sect == NO_SECT)
		c = 'U';
	ft_memset(bytes, ' ', 19);
	bytes[19] = '\0';
	if (list[order[n]].n_type == 1)
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
	if (!(order = ft_get_order(nsyms, stringtable, list)))
		return (FALSE);
	n = 0;
	while (n < nsyms)
		ft_display(stringtable, list, order, n++);
	free(order);
	return (TRUE);
}

static void			ft_header_64(t_buffer file)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)file.bytes;
	lc = (void *)file.bytes + sizeof(*header);
	for (int n = 0 ; n < header->cmds ; ++ n)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_print(sym->nsyms, sym->symoff, sym->stroff, file.bytes);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

static t_bool		ft_nm(const char *path)
{
	int				fd;
	struct stat		buf;
	t_buffer		file;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (FALSE);
	if (fstat(fd, &buf) == -1)
		return (FALSE);
	if (!ft_map_file(fd, buf.st_size, &file))
		return (FALSE);
	if (!ft_magic_number(path, file, &ft_header_64))
		return (FALSE);
	if (!ft_unmap_file(&file))
		return (FALSE);
	return (TRUE);
}

int					main(int ac, char **av)
{
	int		n;

	if (ac == 1)
	{
		if (!ft_nm("a.out"))
			return (1);
	}
	else
	{
		n = 1;
		while (n < ac)
			if (!ft_nm(av[n++]))
				return (1);
	}
	return (0);
}
