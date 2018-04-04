/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:04 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/29 09:02:15 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mach-o/nlist.h>

#include "types.h"
#include "nm_otool.h"

static char			ft_get_type_nsect(t_types *types, uint32_t n_sect)
{
	if (!types)
		return ('S');
	while (types && types->n_sect != n_sect)
		types = types->next;
	return ((types) ? types->type : (char)'S');
}

extern char			ft_get_type(uint32_t n_sect, uint32_t n_type, t_types *types)
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
		c = ft_get_type_nsect(types, n_sect);
	if ((n_type & N_EXT) == 0 && c != ' ')
		c = (char)(c - 'A' + 'a');
	return (c);
}
