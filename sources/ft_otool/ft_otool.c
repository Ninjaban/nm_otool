/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:18:33 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/29 08:19:25 by jcarra           ###   ########.fr       */
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

static t_bool		ft_error(uint32_t n)
{
	ft_putstr("Error : ");
	ft_putnbr(n);
	ft_putstr(".\n");
	return (FALSE);
}

static t_bool		ft_otool(const char *path)
{
	int				fd;
	struct stat		buf;
	t_buffer		file;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_error(1));
	if (fstat(fd, &buf) == -1)
		return (ft_error(2));
	if (!S_ISREG(buf.st_mode))
	{
		close(fd);
		return (ft_error(3));
	}
	if (!ft_map_file(fd, buf.st_size, &file))
		return (ft_error(4));
	if (!ft_magic_number(path, file))
		return (ft_error(5));
	if (!ft_unmap_file(&file))
		return (ft_error(6));
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
