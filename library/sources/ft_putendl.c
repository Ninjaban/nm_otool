/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:47:46 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/23 14:48:34 by jcarra           ###   ########.fr       */
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

void		ft_putendl(char *str)
{
	char	*tmp;

	if (str != NULL)
	{
		if (ft_putcheck(str))
		{
			tmp = ft_eval(str);
			write(1, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else
			write(1, str, ft_strlen(str));
	}
	else
		write(1, "(null)", ft_strlen("(null)"));
	ft_putchar('\n');
}
