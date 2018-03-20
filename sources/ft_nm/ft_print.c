/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:04 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/20 08:35:07 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>

extern char			ft_get_type(uint32_t n_sect, uint32_t n_type,
			struct load_command *lc, char (*f)(uint32_t, struct load_command *))
{
	char		c;

	c = ' ';
	if ((n_type & N_TYPE) == N_UNDF || (n_type & N_TYPE) == N_PBUD)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else if ((n_type & N_TYPE) == N_SECT)
		c = f(n_sect, lc);
	if ((n_type & N_EXT) == 0 && c != ' ')
		c = (char)(c - 'A' + 'a');
	return (c);
}
