/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 09:19:31 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/06 12:38:37 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mach-o/fat.h>
#include "types.h"
#include "nm_otool.h"

uint32_t        swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

extern t_bool		ft_header_fat(t_buffer file)
{
	struct fat_arch		*arch;
	uint32_t			arch_size;
	t_buffer			fat;
	t_bool				(*f[3])(t_buffer);

	BUFFER_SETUP(fat, file.size, file.bytes);
	arch_size = swap_uint32(((struct fat_header *)fat.bytes)->nfat_arch);
	arch = fat.bytes + sizeof((struct fat_header *)fat.bytes);
	while (arch_size)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
		{
			fat.bytes += swap_uint32(arch->offset);
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
