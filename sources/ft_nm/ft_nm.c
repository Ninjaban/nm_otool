/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:20:59 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/29 10:27:41 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>			/* |open()| */
#include <unistd.h>			/* |fstat()| */
#include <sys/mman.h>		/* |mmap()|, |munmap()| */
#include <mach-o/loader.h>	/* |MH_MAGIC_64|, |mach_header_64|, |load_command|, |symtab_command| */
#include <mach-o/nlist.h>	/* |nlist_64| */
#include <types.h>
#include <stdlib.h>

#include "types.h"
#include "error.h"
#include "libft.h"

/* -- basic check */
typedef char __check_for_example_true[ (TRUE == 1) ? 1:-1 ];
typedef char __check_for_example_false[ (FALSE == 0) ? 1:-1 ];


/* -- library_configuration */
static struct
{
	t_bool	initialized;

	t_bool	debug_mode;
} internal_context = {
		.initialized	= FALSE,

		.debug_mode	= FALSE
};


/**
 *		internal_context_is_initialize
 *
 *		@param	none
 *
 *		@error	none
 *
 *		@return	TRUE in success, FALSE otherwise
 */
static t_bool		internal_context_is_initialize (void)
{
	return (internal_context.initialized);
}


/* === initialisation function === */
/**
 *		internal_context_initialize
 *
 *		@param	none
 *
 *		@error	none
 */
static void			internal_context_initialize (void)
{
	internal_context.initialized = TRUE;

	internal_context.debug_mode = DEBUG_MODE;
}


//		TEMP double
t_bool				ft_map_file(const int fd, const off_t size, t_buffer *file)
{
	void			*bytes;

	if (file == NULL)
	{
		FT_ERROR("ptr %p", file);
		return (FALSE);
	}

	if (!(bytes = mmap(0, (size_t )size, PROT_READ, MAP_PRIVATE, fd, 0)))
	{
		FT_ERROR("mmap() failed size %" PRIu64 " fd %" PRIu32, size, fd);
		return (TRUE);
	}

	BUFFER_SETUP(*file, size, bytes);

	return (TRUE);
}


//		TEMP double
t_bool				ft_unmap_file(t_buffer *file)
{
	if ((*file).bytes == NULL)
	{
		FT_ERROR("ptr %p", (*file).bytes);
		return (FALSE);
	}

	if (munmap((*file).bytes, (*file).size) == -1)
	{
		FT_ERROR("munmap() failed ptr %p size %" PRIu32, (*file).bytes, (*file).size);
		return (TRUE);
	}

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
	if (n_sect  == 11 && n_type == 15)
		return ('D');
	if (n_sect == 12 && n_type == 14)
		return ('s');
	if (n_sect  == 12 && n_type == 15)
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

//		FT_DEBUG("n_type %" PRIu8 " n_sect %" PRIu8, list[order[n]].n_type, list[order[n]].n_sect);
		if (list[order[n]].n_type == 1)
			FT_DEBUG("%s %c %s",
					 "                ",
					 c,
					 stringtable + list[order[n]].n_un.n_strx);
		else
			FT_DEBUG("%s%08x %c %s",
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
			sym = (struct symtab_command *) lc;

			ft_print(sym->nsyms, sym->symoff, sym->stroff, file.bytes);

			FT_DEBUG("nb symbole %d", sym->nsyms);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}

	return (TRUE);
}

t_bool				ft_magic_number(t_buffer file)
{
	t_uint					magic_number;

	magic_number = *(int *)file.bytes;

	if (magic_number == MH_MAGIC_64)
		ft_header_64(file);

	return (TRUE);
}


t_bool				ft_nm(const char *path)
{
	int				fd;
	struct stat		buf;
	t_buffer		file;


	if (!internal_context_is_initialize())
	{
		FT_ERROR("internal_context not initialize %s", "");
		return (FALSE);
	}

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		FT_ERROR("open() failed path %s", path);
		return (FALSE);
	}

	if (fstat(fd, &buf) == -1)
	{
		FT_ERROR("fstat() failed fd %" PRIu32, fd);
		return (FALSE);
	}

	FT_DEBUG("%s is valid", path);

	if (!ft_map_file(fd, buf.st_size, &file))
	{
		FT_WARNING("ft_map_file() failed fd %" PRIu32 " size %" PRIu64, fd, buf.st_size);
		return (FALSE);
	}

	FT_DEBUG("%s is maped size %" PRIu32 " {%.*s}", path, file.size, file.size, file.bytes);

	if (!ft_magic_number(file))
	{
		FT_WARNING("ft_magic_number() failed %s", "");
		return (FALSE);
	}

	if (!ft_unmap_file(&file))
	{
		FT_WARNING("ft_unmap_file() failed {%.*s}", file.size, file.bytes);
		return (FALSE);
	}

	return (TRUE);
}

int					main(int ac, char **av)
{
	int		n;

	internal_context_initialize();

	if (ac == 1)
	{
		if (!ft_nm("a.out"))
		{
			FT_WARNING("ft_nm() failed path %s", "a.out");
			return (1);
		}
	}
	else
	{
		n = 1;
		while (n < ac)
			if (!ft_nm(av[n++]))
			{
				FT_WARNING("ft_nm() failed file %d path %s", n - 1, av[n - 1]);
				return (1);
			}
	}
	return (0);
}