/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 10:04:33 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 09:01:23 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int			ft_end(int ret, int size)
{
	if (ret == -1)
		return (-1);
	if (ret == 0 && size > 0)
		return (1);
	if (ret == 0 && size == 0)
		return (0);
	return (0);
}

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i = i + 1;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

char		*ft_alloc(char **line, size_t len)
{
	char	*str;

	if ((str = ft_strnew(len + BUFFER_SIZE)) == NULL)
		return (NULL);
	if (len == 0)
		return (str);
	ft_strncpy(str, (*line), len);
	free(*line);
	return (str);
}

int			ft_get_next_line(int const fd, char **line, size_t size, size_t n)
{
	int		ret;
	char	c;

	while (42)
	{
		(*line) = ft_alloc(line, size);
		while (size < BUFFER_SIZE * n)
		{
			ret = read(fd, &c, 1);
			(*line)[size] = '\0';
			if (ret > 0)
			{
				if (c == DEL)
					return (1);
				(*line)[size] = c;
			}
			else
				return (ft_end(ret, size));
			size = size + 1;
		}
		(*line)[size] = '\0';
		n = n + 1;
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	if (!line)
		return (-1);
	return (ft_get_next_line(fd, &(*line), 0, 1));
}
