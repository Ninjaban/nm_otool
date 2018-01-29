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

# define BUFFER_CLEAR(target)									\
{																\
(target).size = 0;												\
(target).bytes = NULL;											\
}
# define BUFFER_SETUP(target, size, bytes)						\
{																\
(target).size = (size);											\
(target).bytes = (bytes);										\
}
# define BUFFER_CHECK(target)									\
{																\
	(((target).size == 0) && ((target).bytes == NULL)) ||		\
	(((target).size >  0) && ((target).bytes != NULL)) ||		\
}

#endif
