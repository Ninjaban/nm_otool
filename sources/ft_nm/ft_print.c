/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:04 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/09 16:07:27 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>

static void			ft_init(char (*tab)[17][31])
{
	uint32_t	n;
	uint32_t	i;

	n = 0;
	while (n <= 16)
	{
		i = 0;
		while (i <= 30)
		{
			(*tab)[n][i] = ' ';
			i = i + 1;
		}
		n = n + 1;
	}
}

static void			ft_init_char(char (*tab)[17][31], uint32_t pos, char c,
									char nb)
{
	if (nb == 1 || nb == 3 || nb == 5 || nb == 7)
		(*tab)[pos][14] = c;
	if (nb == 2 || nb == 3 || nb == 6 || nb == 7)
		(*tab)[pos][15] = (char)(c - 'a' + 'A');
	if (nb == 4 || nb == 5 || nb == 6 || nb == 7)
		(*tab)[pos][30] = c;
}

extern char			ft_nsect_decription(uint32_t n_sect, uint32_t n_type)
{
	char		tab[17][31];

	ft_init(&tab);
	ft_init_char(&tab, 1, 't', 7);
	ft_init_char(&tab, 4, 's', 1);
	ft_init_char(&tab, 5, 's', 1);
	ft_init_char(&tab, 6, 's', 2);
	ft_init_char(&tab, 8, 'd', 2);
	ft_init_char(&tab, 9, 'b', 3);
	ft_init_char(&tab, 10, 's', 2);
	ft_init_char(&tab, 11, 'd', 3);
	ft_init_char(&tab, 12, 'b', 1);
	ft_init_char(&tab, 12, 's', 2);

	/*
	tab[1][14] = 't';
	tab[1][15] = 'T';
	tab[1][30] = 't';
	tab[4][14] = 's';
	tab[5][14] = 's';
	tab[6][15] = 'S';
	tab[8][15] = 'D';
	tab[9][14] = 'b';
	tab[9][15] = 'B';
	tab[10][15] = 'S';
	tab[11][14] = 'd';
	tab[11][15] = 'D';
	tab[12][14] = 'b';
	tab[12][15] = 'S';
	 */

	ft_init_char(&tab, 13, 'd', 7);
	ft_init_char(&tab, 14, 's', 4);
	ft_init_char(&tab, 15, 'b', 1);
	ft_init_char(&tab, 16, 's', 2);

	/*
	tab[13][14] = 'd';
	tab[13][15] = 'D';
	tab[13][30] = 'd';
	tab[14][30] = 's';
	tab[15][14] = 'b';
	tab[16][15] = 'S';
	 */
	return ((n_sect > 16 || n_type > 30) ? (char)' ' : tab[n_sect][n_type]);
}
