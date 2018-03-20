/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:50 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/20 13:37:34 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "libft.h"
#include "types.h"
#include "nm_otool.h"

/*
**	ft_map_file()
**
**	map a file descriptor in memory and set the buffer with the value.
**
**	@param		fd		file descriptor
**	@param		size	file size
**	@param		file	out buffer
**
**	@return	TRUE in success, FALSE otherwise
*/

extern t_bool		ft_map_file(const int fd, const off_t size, t_buffer *file)
{
	void			*bytes;

	if (file == NULL)
		return (FALSE);
	if (!(bytes = mmap(0, (size_t)size, PROT_READ, MAP_PRIVATE, fd, 0)))
		return (FALSE);
	BUFFER_SETUP(*file, size, bytes);
	ft_check_addr(file->bytes, file->bytes + file->size, NULL, 0);
	return (TRUE);
}

/*
**	ft_unmap_file()
**
**	release memory of a maped file.
**
**	@param		file	in buffer
**
**	@return	TRUE in success, FALSE otherwise
*/

extern t_bool		ft_unmap_file(t_buffer *file)
{
	if ((*file).bytes == NULL)
		return (FALSE);
	if (munmap((*file).bytes, (*file).size) == -1)
		return (FALSE);
	BUFFER_CLEAR(*file);
	return (TRUE);
}

/*
**	ft_magic_number()
**
**	check the magic number in the buffer file and call the function f
**
**	@param		path	complete path of the file
**	@param		file	in buffer
**	@param		f		function
**
**	@return	TRUE in success, FALSE otherwise
*/

extern t_bool		ft_magic_number(const char *path, t_buffer file,
									t_bool (*f[3])(t_buffer))
{
	t_uint					magic_number;

	if (!file.bytes || !file.size)
		return (FALSE);
	magic_number = (t_uint)(*(int *)file.bytes);
	if (path)
	{
		ft_putstr((char *)path);
		if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM ||
			magic_number == MH_MAGIC || magic_number == MH_MAGIC_64)
			ft_putstr(":\n");
		else
			ft_putstr(": is not an object\n");
	}
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (f[ARRAY_FAT](file));
	else if (magic_number == MH_MAGIC)
		return (f[ARRAY_32](file));
	else if (magic_number == MH_MAGIC_64)
		return (f[ARRAY_64](file));
	else
		return (FALSE);
}

extern t_bool		ft_check_addr(void *in_start, void *in_end, void *addr,
								uint32_t size)
{
	static void		*start = NULL;
	static void		*end = NULL;

	if (in_start && in_end)
	{
		start = in_start;
		end = in_end;
		return (TRUE);
	}
	if (!addr)
		return (FALSE);
	if ((start && end) && addr >= start && addr <= end &&
			addr + size >= start && addr + size < end)
		return (TRUE);
	return (FALSE);
}