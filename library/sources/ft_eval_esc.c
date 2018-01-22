/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_esc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:57:18 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/07 15:09:47 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

/*
** char ft_esc_x(eval->tmp, &(eval->n_tmp))
**
** converts the hexadecimal escape sequence to a char
*/

char		ft_esc_x(char *token, size_t *n)
{
	char	c;
	size_t	size;

	c = 0;
	size = 0;
	while (size < 2 && token[*n] && ft_ishex(token[*n]))
	{
		if (ft_isdigit(token[*n]))
			c = (16 * c) + (token[*n] - '0');
		else
			c = (16 * c) + 10 + ('a' <= token[*n]
								&& token[*n] <= 'z'
								? (token[*n] - 'a')
								: (token[*n] - 'A'));
		size++;
		(*n)++;
	}
	(*n)--;
	return (c);
}

/*
** char ft_esc_ansi(eval->tmp, &(eval->n_tmp))
**
** converts the ansi escape sequence to the corresponding value
*/

static char	ft_esc_ansi(char *token, size_t *n)
{
	int	c;

	c = 0;
	while (c < ANSI_MAX && token[*n + 1] != ANSI_C_CHAR[c])
		c++;
	(*n) += 2;
	return (ANSI_LIST[c]);
}

/*
** char ft_esc_oct(eval->tmp, &(eval->n_tmp))
**
** converts the octal escape sequence to a char
*/

static char	ft_esc_oct(char *token, size_t *n)
{
	char	c;
	size_t	size;

	c = 0;
	(*n) += 1;
	size = 0;
	while (size < 3 && token[*n] && ft_isoct(token[*n]))
	{
		c = (8 * c) + (token[*n] - '0');
		size++;
		(*n)++;
	}
	(*n)--;
	return (c);
}

/*
** void ft_esc_c(eval)
**
** identifies the function to use to gets the correct escaped value
** updates eval->buf accordingly
*/

void		ft_esc_c(t_eval *e)
{
	if (IS_ANSI(e->tmp[e->n_tmp + 1]))
		e->buf[e->n_buf] = ft_esc_ansi(e->tmp, &(e->n_tmp));
	else if (IS_ESC_NB(e->tmp[e->n_tmp + 1]))
		ft_esc_hex(e);
	else if (ft_isoct(e->tmp[e->n_tmp + 1]))
		e->buf[e->n_buf] = ft_esc_oct(e->tmp, &(e->n_tmp));
	else
	{
		e->n_tmp++;
		e->buf[e->n_buf] = e->tmp[e->n_tmp];
	}
}
