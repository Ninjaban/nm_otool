/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:47:46 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/23 14:50:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

static char	ft_putcheck(char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
	{
		if (!ft_strncmp(str + n, "\x1b[", 2))
			return (1);
		n = n + 1;
	}
	return (0);
}

void		ft_putendl_fd(char *str, int fd)
{
	char	*tmp;

	if (str != NULL)
	{
		if (ft_putcheck(str))
		{
			tmp = ft_eval(str);
			write(fd, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else
			write(fd, str, ft_strlen(str));
	}
	ft_putchar_fd('\n', fd);
}
