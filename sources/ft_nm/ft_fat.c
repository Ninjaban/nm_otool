/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 09:19:31 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/12 08:17:34 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mach-o/fat.h>
#include "types.h"
#include "nm_otool.h"

uint32_t			swap_bits(uint32_t val)
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

extern t_bool		ft_header_fat(t_buffer file)
{
	struct fat_arch		*arch;
	uint32_t			arch_size;
	t_buffer			fat;
	t_bool				(*f[3])(t_buffer);

	BUFFER_SETUP(fat, file.size, file.bytes);
	arch_size = swap_bits(((struct fat_header *)fat.bytes)->nfat_arch);
	arch = fat.bytes + sizeof((struct fat_header *)fat.bytes);
	while (arch_size)
	{
		if (swap_bits(arch->cputype) == CPU_TYPE_X86_64)
		{
			fat.bytes += swap_bits(arch->offset);
			break ;
		}
		arch += sizeof(struct fat_arch);
		arch_size = arch_size - 1;
	}
	f[ARRAY_FAT] = ft_header_fat;
	f[ARRAY_32] = ft_header_32;
	f[ARRAY_64] = ft_header_64;
	return (ft_magic_number(NULL, fat, f));
}
