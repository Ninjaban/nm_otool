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
#include <unistd.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "libft.h"

/*
** -- basic check
*/
typedef char	t__check_for_ft_nm_true[(TRUE == 1) ? 1 : -1];
typedef char	t__check_for_ft_nm_false[(FALSE == 0) ? 1 : -1];

//		TEMP double
t_bool				ft_map_file(const int fd, const off_t size, t_buffer *file)
{
	void			*bytes;

	if (file == NULL)
		return (FALSE);
	if (!(bytes = mmap(0, (size_t)size, PROT_READ, MAP_PRIVATE, fd, 0)))
		return (TRUE);
	BUFFER_SETUP(*file, size, bytes);
	return (TRUE);
}

//		TEMP double
t_bool				ft_unmap_file(t_buffer *file)
{
	if ((*file).bytes == NULL)
		return (FALSE);
	if (munmap((*file).bytes, (*file).size) == -1)
		return (TRUE);
	BUFFER_CLEAR(*file);
	return (TRUE);
}

char				ft_nsect_decription(uint32_t n_sect, uint32_t n_type)
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

t_bool				ft_print(uint32_t nsyms, int symoff, int stroff, void *ptr)
{
	char			c;
	uint32_t		n;
	uint32_t		tmp;
	uint32_t		*order;
	char			*stringtable;
	struct nlist_64	*list;

	list = ptr + symoff;
	stringtable = ptr + stroff;
	order = malloc(sizeof(uint32_t) * nsyms);
	n = 0;
	while (n < nsyms)
	{
		order[n] = n;
		n = n + 1;
	}
	n = 0;
	while (n < nsyms)
	{
		if (n + 1 < nsyms && ft_strcmp(stringtable + list[order[n]].n_un.n_strx, stringtable + list[order[n + 1]].n_un.n_strx) >= 0)
		{
			tmp = order[n];
			order[n] = order[n + 1];
			order[n + 1] = tmp;
			n = 0;
		}
		else
			n = n + 1;
	}
	for (n = 0 ; n < nsyms ; ++ n)
	{
		c = ' ';
		if (list[order[n]].n_type >= N_SECT)
			c = ft_nsect_decription(list[order[n]].n_sect, list[order[n]].n_type);
		else if (list[order[n]].n_sect == NO_SECT)
			c = 'U';
		if (list[order[n]].n_type == 1)
			printf("%s %c %s\n",
					"                ",
					c,
					stringtable + list[order[n]].n_un.n_strx);
		else
			printf("%s%08x %c %s\n",
					"00000001",
					(uint32_t)list[order[n]].n_value,
					c,
					stringtable + list[order[n]].n_un.n_strx);
	}
	free(order);
	return (TRUE);
}

t_bool				ft_header_64(t_buffer file)
{
	int						ncmds;
	struct load_command		*lc;
	struct mach_header_64	*header;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)file.bytes;
	ncmds = header->ncmds;
	lc = (void *)file.bytes + sizeof(*header);
	for (int n = 0 ; n < ncmds ; ++ n)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_print(sym->nsyms, sym->symoff, sym->stroff, file.bytes);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (TRUE);
}

t_bool				ft_magic_number(t_buffer file)
{
	t_uint					magic_number;

	magic_number = (t_uint)(*(int *)file.bytes);
	if (magic_number == MH_MAGIC_64)
		ft_header_64(file);
	return (TRUE);
}

t_bool				ft_nm(const char *path)
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
	if (!ft_magic_number(file))
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
