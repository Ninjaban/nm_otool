/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:44:04 by jcarra            #+#    #+#             */
/*   Updated: 2018/02/14 15:44:03 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <stdlib.h>
#include "libft.h"

extern char			ft_nsect_decription(uint32_t n_sect, uint32_t n_type)
{
	if (n_sect == 1 && n_type == 14)
		return ('t');
	if (n_sect == 1 && n_type == 15)
		return ('T');
	if (n_sect == 9 && n_type == 14)
		return ('b');
	if (n_sect == 9 && n_type == 15)
		return ('B');
	if (n_sect == 11 && n_type == 14)
		return ('d');
	if (n_sect == 11 && n_type == 15)
		return ('D');
	if (n_sect == 12 && n_type == 14)
		return ('s');
	if (n_sect == 12 && n_type == 15)
		return ('S');
	if (n_sect == 10 && n_type == 15)
		return ('S');
	return (' ');
}
