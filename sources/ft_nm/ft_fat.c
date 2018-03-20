/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 09:19:31 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/20 16:14:17 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mach-o/fat.h>
#include <printf.h>
#include "types.h"
#include "nm_otool.h"

static uint32_t		swap_bits(uint32_t val)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;

	a = (((val >> 16) & 0xFF) << 8);
	b = (((val >> 16) & 0xFF00) >> 8);
	c = (((val << 16) & 0xFF0000) << 8);
	d = (((val << 16) & 0xFF000000) >> 8);
	val = a | b | c | d;
	return (val);
}

static t_bool		ft_header_fat_call(t_buffer file)
{
	t_bool				(*f[3])(t_buffer);

	f[ARRAY_FAT] = ft_header_fat;
	f[ARRAY_32] = ft_header_32;
	f[ARRAY_64] = ft_header_64;
	return (ft_magic_number(NULL, file, f));
}

extern t_bool		ft_header_fat(t_buffer file)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			arch_size;
	uint32_t			offset;

	fat = (struct fat_header *)file.bytes;
	if (!(CHECK_ADDR(fat, sizeof(struct fat_header *))))
		return (FALSE);
	arch = (struct fat_arch *)(fat + 1);
	arch_size = swap_bits(fat->nfat_arch);
	offset = 0;
	while (arch_size)
	{
		if (!(CHECK_ADDR(arch, sizeof(struct fat_arch *))))
			return (FALSE);
		if (swap_bits(arch->cputype) == CPU_TYPE_X86_64)
			offset = swap_bits(arch->offset);
		arch += 1;
		arch_size = arch_size - 1;
	}
	if (!offset)
		return (FALSE);
	BUFFER_SETUP(file, file.size - offset, file.bytes + offset);
	return (ft_header_fat_call(file));
}
