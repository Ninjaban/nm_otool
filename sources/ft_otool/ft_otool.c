/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:18:33 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/29 15:36:23 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>			/* |open()| */
#include <unistd.h>			/* |fstat()| */
#include <sys/mman.h>		/* |mmap()|, |munmap()| */
#include <mach-o/loader.h>	/* |MH_MAGIC_64|, |mach_header_64|, |load_command|, |symtab_command| */
#include <mach-o/nlist.h>	/* |nlist_64| */

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


t_bool				ft_print(uint64_t addr, const uint64_t size, const char *ptr)
{
	char			buf[75];
	int				buf_size;
	int				sprintf_ret;
	uint64_t		n;

	n = 0;
	while (n < size)
	{
		if (n == 0 || n % 16 == 0)
		{
			addr = (n != 0) ? addr + 16 : addr;
			buf_size = sprintf(buf, "00000001%08x", (t_uint)addr);
		}
		sprintf_ret = sprintf(buf + buf_size, " %02x", ptr[n]);
		if (sprintf_ret > 3)
		{
			buf[buf_size + 1] = buf[buf_size + sprintf_ret - 2];
			buf[buf_size + 2] = buf[buf_size + sprintf_ret - 1];
		}
		buf_size += 3;
		if ((n + 1) % 16 == 0 || n + 1 == size)
		{
			buf[buf_size++] = '\n';
			buf[buf_size] = '\0';
			ft_putstr(buf);
		}
		n += 1;
	}
	return (TRUE);
}


t_bool				ft_segment(struct segment_command_64 *seg, t_buffer file)
{
	struct section_64		*sec;
	t_uint					n;

	n = 0;
	sec = (struct section_64 *)(seg + 1);
	while (n < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, SECT_TEXT) && !ft_strcmp(sec->segname, SEG_TEXT))
		{
			FT_DEBUG("Contents of (__TEXT,__text) section %s", "");
			ft_print(sec->addr, sec->size, file.bytes + sec->offset);
		}

		sec += 1;
		n += 1;
	}
	return (TRUE);
}


t_bool				ft_header_64(t_buffer file)
{
	struct load_command			*lc;
	struct mach_header_64		*header;

	header = (struct mach_header_64 *)file.bytes;
	lc = (void *)file.bytes + sizeof(*header);

	for (t_uint n = 0 ; n < header->ncmds ; ++ n)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			FT_DEBUG("ft_segment() %s", "");
			ft_segment((struct segment_command_64 *)lc, file);
		}
		lc = (void *)lc + lc->cmdsize;
	}

	return (TRUE);
}


//		TEMP double
t_bool				ft_magic_number(const char *path, t_buffer file)
{
	t_uint					magic_number;

	magic_number = *(int *)file.bytes;

	if (magic_number == MH_MAGIC_64)
	{
		FT_DEBUG("%s:", path);
		ft_header_64(file);
	}
	else
	{
		FT_DEBUG("%s: is not an object", path);
		return (FALSE);
	}

	return (TRUE);
}


t_bool				ft_otool(const char *path)
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

	if (!ft_magic_number(path, file))
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
		FT_WARNING("Usage: ft_otool [file1] ... %s", "");
		return (1);
	}
	else
	{
		n = 1;
		while (n < ac)
			if (!ft_otool(av[n++]))
			{
				FT_WARNING("ft_otool() failed file %d path %s", n - 1, av[n - 1]);
				return (1);
			}
	}
	return (0);
}