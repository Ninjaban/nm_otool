/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:18:33 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/29 16:15:52 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

/*
** -- basic check
*/
typedef char	t__check_for_ft_otool_true[(TRUE == 1) ? 1 : -1];
typedef char	t__check_for_ft_otool_false[(FALSE == 0) ? 1 : -1];

static t_bool		ft_print(uint64_t addr, const uint64_t size,
							const char *ptr)
{
	char			buf[75];
	int				buf_size;
	uint64_t		n;

	n = 0;
	while (n < size)
	{
		if (n == 0 || n % 16 == 0)
		{
			addr = (n != 0) ? addr + 16 : addr;
			buf_size = ft_itohex((int)addr, buf, 16);
		}
		buf[buf_size] = ' ';
		buf_size = ft_itohex(ptr[n++], buf + buf_size + 1, 2);
		buf_size += 3;
		if (n % 16 == 0 || n == size)
		{
			buf[buf_size++] = '\n';
			buf[buf_size] = '\0';
			ft_putstr(buf);
		}
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
		if (!ft_strcmp(sec->sectname, SECT_TEXT) &&
				!ft_strcmp(sec->segname, SEG_TEXT))
		{
			ft_putstr("Contents of (__TEXT,__text) section\n");
			ft_print(sec->addr, sec->size, file.bytes + sec->offset);
		}
		sec += 1;
		n += 1;
	}
	return (TRUE);
}

static void			ft_header_64(t_buffer file)
{
	struct load_command			*lc;
	struct mach_header_64		*header;
	t_uint						n;

	header = (struct mach_header_64 *)file.bytes;
	lc = (void *)file.bytes + sizeof(*header);
	n = 0;
	while (n < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_segment((struct segment_command_64 *)lc, file);
		lc = (void *)lc + lc->cmdsize;
		n += 1;
	}
}

static t_bool		ft_otool(const char *path)
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
		ft_putstr("Usage: ft_otool [file1] ...\n");
		return (1);
	}
	n = 1;
	while (n < ac)
		if (!ft_otool(av[n++]))
		{
			ft_putstr("Usage: ft_otool [file1] ...\n");
			return (1);
		}
	return (0);
}
