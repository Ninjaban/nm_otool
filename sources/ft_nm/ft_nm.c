/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:20:59 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/13 10:05:31 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <unistd.h>

#include "types.h"
#include "nm_otool.h"

/*
** -- basic check
*/
typedef char		t__check_for_ft_nm_true[(TRUE == 1) ? 1 : -1];
typedef char		t__check_for_ft_nm_false[(FALSE == 0) ? 1 : -1];





static t_bool		ft_nm(const char *path, t_bool print_name)
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
	if (!ft_magic_number((print_name) ? path : NULL, file, &ft_header_64, &ft_header_32))
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
		if (!ft_nm("a.out", FALSE))
			return (1);
	}
	else
	{
		n = 1;
		while (n < ac)
			if (!ft_nm(av[n++], (ac == 2) ? FALSE : TRUE))
				return (1);
	}
	return (0);
}
