/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:42:22 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/19 11:20:20 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

#include "libft.h"
#include "types.h"

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
			buf_size = ft_itohex(addr, buf, 16);
		}
		buf[buf_size] = ' ';
		ft_itohex(ptr[n++], buf + buf_size + 1, 2);
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

static t_bool		ft_segment(struct segment_command_64 *seg, t_buffer file)
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

extern void			ft_header_64(t_buffer file)
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
