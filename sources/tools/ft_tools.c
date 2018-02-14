/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:50 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/13 10:00:46 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include "libft.h"
#include "types.h"

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
									t_bool (f64)(t_buffer),
									t_bool (f32)(t_buffer))
{
	t_uint					magic_number;

	magic_number = (t_uint)(*(int *)file.bytes);
	if (path)
		ft_putstr((char *)path);
	if (magic_number == MH_MAGIC_64)
	{
		if (path)
			ft_putstr(":\n");
		return (f64(file));
	}
	else if (magic_number == MH_MAGIC)
	{
		if (path)
			ft_putstr(":\n");
		return (f32(file));
	}
	else
	{
		if (path)
			ft_putstr(": is not an object\n");
		return (FALSE);
	}
	return (TRUE);
}
