/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:20:59 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/22 11:45:27 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		/* |open()| */
#include <unistd.h>		/* |fstat()| */

#include "types.h"
#include "error.h"

/* -- library_configuration */
static struct
{
	t_bool	initialized;

	t_bool	debug_mode;
} internal_context = {
		.initialized	= FALSE,

		.debug_mode	= FALSE
};


/**
 *		internal_context_is_initialize
 *
 *		@param	none
 *
 *		@error	none
 *
 *		@return	TRUE in success, FALSE otherwise
 */
static t_bool		internal_context_is_initialize (void)
{
	return (internal_context.initialized);
}


/* === initialisation function === */
/**
 *		internal_context_initialize
 *
 *		@param	none
 *
 *		@error	none
 */
static void			internal_context_initialize (void)
{
	internal_context.initialized = TRUE;

	internal_context.debug_mode = DEBUG_MODE;
}


t_bool				ft_nm(const char *path)
{
	int				fd;
	struct stat		buf;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		FT_ERROR("open() failed %s", "");
		return (FALSE);
	}

	if (fstat(fd, &buf) == -1 && !(buf.st_mode & S_IXOTH))
	{
		FT_ERROR("fstat() failed %s", "");
		return (FALSE);
	}

	FT_DEBUG("%s is valid", path);


	return (TRUE);
}

int					main(int ac, char **av)
{
	int		n;

	internal_context_initialize();

	if (ac == 1)
	{
		if (!ft_nm("a.out"))
		{
			FT_WARNING("ft_nm() failed %s", "");
			return (1);
		}
	}
	else
	{
		n = 1;
		while (n < ac)
			if (!ft_nm(av[n++]))
			{
				FT_WARNING("ft_nm() failed %s", "");
				return (1);
			}
	}
	return (0);
}