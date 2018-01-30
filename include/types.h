/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:17:40 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/29 16:27:54 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_TYPES_H
# define NM_OTOOL_TYPES_H

# include <stdint.h>

# define TRUE		1
# define FALSE		0

typedef char				t_bool;
typedef void *				t_pvoid;
typedef char *				t_pchar;
typedef unsigned int		t_uint;

typedef struct				s_buffer
{
	t_uint					size;
	t_pvoid					bytes;
}							t_buffer;

/*
**	buffer define
**
**	@param		t	(target)	target buffer
**	@param		s	(size)		size of the pointer
**	@param		b	(bytes)		pointer
*/
# define BUFFER_CLEAR(t)		{(t).size = 0; (t).bytes = NULL;}
# define BUFFER_SETUP(t, s, b)	{(t).size = (s); (t).bytes = (b);}

#endif
