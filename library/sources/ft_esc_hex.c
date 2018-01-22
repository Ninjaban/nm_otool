/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:17:54 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/07 14:47:44 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

/*
** ISO/IEC 10646
** 1 byte	00000000 - 0000007F	0.7
** 2 bytes	00000080 - 000007FF	110.5		10.6
** 3 bytes	00000800 - 0000FFFF	1110.4		10.6 10.6
** 4 bytes	00010000 - 001FFFFF	11110.3		10.6 10.6 10.6 (0010fff)
** 5 bytes	00200000 - 03FFFFFF	111110.2	10.6 10.6 10.6 10.6
** 6 bytes	04000000 - 7FFFFFFF	1111110.1	10.6 10.6 10.6 10.6 10.6
**
**	0x00 | ((0x7f << 0	& c) >> 0)
**	0xc0 | ((0x1F << 6	& c) >> 6)
**	0xe0 | ((0x0F << 12	& c) >> 12)
**	0xf0 | ((0x07 << 18	& c) >> 18)
** 	0xf8 | ((0x03 << 24	& c) >> 24)
**	0xfc | ((0x01 << 30	& c) >> 30)
**
** 0x80 | ((0x3F << (6 * n) & c) >> (6 * n))
*/

/*
** char ft_get_max(int c)
**
** returns the number of char to add to eval->buf
*/

static char	ft_get_max(int c)
{
	if (c <= 0x7f)
		return (1);
	else if (c <= 0x7ff)
		return (2);
	else if (c <= 0xffff)
		return (3);
	else if (c <= 0x1fffff)
		return (4);
	else if (c <= 0x3ffffff)
		return (5);
	else
		return (6);
}

/*
** char ft_get_esc(c, n, max)
**
** returns the char to be placed in buf[nbuf + m],
** according to the unicode pattern, using bitwise operations
*/

static char	ft_get_esc(int c, int n, int max)
{
	if (n != 6 * (max - 1))
		return (0x80 | (0x3f << (n) & c) >> (n));
	else if (c <= 0x7f)
		return (0x00 | (0x7f << (6 * 0) & c) >> (6 * (max - 1)));
	else if (c <= 0x7ff)
		return (0xc0 | (0x1f << (6 * 1) & c) >> (6 * (max - 1)));
	else if (c <= 0xffff)
		return (0xe0 | (0x0f << (6 * 2) & c) >> (6 * (max - 1)));
	else if (c <= 0x1fffff)
		return (0xf0 | (0x07 << (6 * 3) & c) >> (6 * (max - 1)));
	else if (c <= 0x3ffffff)
		return (0xf8 | (0x03 << (6 * 4) & c) >> (6 * (max - 1)));
	else
		return (0xfc | (0x01 << (6 * 5) & c) >> (6 * (max - 1)));
}

/*
** void ft_unicode_val(eval, c)
**
** adds the corresponding sequence of char to eval->buf with ft_get_esc
*/

static void	ft_unicode_val(t_eval *e, int c)
{
	int		max;
	int		n;
	int		m;

	max = ft_get_max(c);
	n = 6 * (max - 1);
	m = 0;
	while (m < max)
	{
		e->buf[e->n_buf + m] = ft_get_esc(c, n, max);
		n -= 6;
		m++;
	}
	e->n_buf += (max - 2);
}

/*
** void ft_unicode(eval, x)
**
** converts the hexadecimal escape sequence to an int
** updates eval->buf with ft_unicode_val
*/

static void	ft_unicode(t_eval *e, int x)
{
	int		c;
	size_t	size;

	c = 0;
	size = 0;
	while (size < ESC_NB_S[x] && e->tmp[e->n_tmp] && ft_ishex(e->tmp[e->n_tmp]))
	{
		if (ft_isdigit(e->tmp[e->n_tmp]))
			c = (16 * c) + (e->tmp[e->n_tmp] - '0');
		else
			c = (16 * c) + 10 + ('a' <= e->tmp[e->n_tmp]
								&& e->tmp[e->n_tmp] <= 'z'
								? (e->tmp[e->n_tmp] - 'a')
								: (e->tmp[e->n_tmp] - 'A'));
		size++;
		e->n_tmp++;
	}
	e->n_tmp--;
	ft_unicode_val(e, c);
}

/*
** void ft_esc_hex(eval)
**
** checks the type of escape sequence (hex or unicode)
** uptdates eval->buf with ft_esc_x (see ft_eval_esc.c) or ft_unicode
*/

void		ft_esc_hex(t_eval *e)
{
	int		x;

	x = 0;
	while (e->tmp[e->n_tmp + 1] != ESC_NB[x])
		x++;
	e->n_tmp += 2;
	if (x == 0)
		e->buf[e->n_buf] = ft_esc_x(e->tmp, &(e->n_tmp));
	else
		ft_unicode(e, x);
}
