/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:20:59 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/09 16:13:45 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <unistd.h>

#include "libft.h"
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
	t_bool			(*f[3])(t_buffer);

	if ((fd = open(path, O_RDONLY)) == -1)
		return (FALSE);
	if (fstat(fd, &buf) == -1)
		return (FALSE);
	if (!ft_map_file(fd, buf.st_size, &file))
		return (FALSE);
	f[ARRAY_FAT] = ft_header_fat;
	f[ARRAY_32] = ft_header_32;
	f[ARRAY_64] = ft_header_64;
	if (!ft_magic_number((print_name) ? path : NULL, file, f))
	{
		ft_putstr_fd("Une erreur est survenue.\n", 2);
		return (FALSE);
	}
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
