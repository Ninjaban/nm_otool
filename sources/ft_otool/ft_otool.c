/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:18:33 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/13 09:43:02 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <stdio.h>
#include "libft.h"
#include "types.h"
#include "nm_otool.h"

/*
** -- basic check
*/
typedef char	t__check_for_ft_otool_true[(TRUE == 1) ? 1 : -1];
typedef char	t__check_for_ft_otool_false[(FALSE == 0) ? 1 : -1];


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
	if (!ft_magic_number(path, file, &ft_header_64, &ft_header_32))
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
