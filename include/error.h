/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:04:01 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/22 11:31:34 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NM_OTOOL_ERROR_H
#define NM_OTOOL_ERROR_H

#include <stdio.h>		/* |fprintf()| */
#include <inttypes.h>	/* |PRIu64| */
#include <stdint.h>		/* |uint64_t| */
#include <stdarg.h>		/* |__VA_ARGS__| */

#define FT_DEBUG(in_context, ...)													\
	do {																			\
	if (internal_context.debug_mode == TRUE) {										\
		(void) fprintf (stderr, "DEBUG:%s:%" PRIu64 ":%s: " in_context "\n",		\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
		}																			\
	} while (0)

#define FT_WARNING(in_context, ...)													\
	do {																			\
	(void) fprintf (stderr, "WARNING:%s:%" PRIu64 ":%s: " in_context "\n",			\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
	} while (0)

#define FT_ERROR(in_context, ...)													\
	do {																			\
	(void) fprintf (stderr, "ERROR:%s:%" PRIu64 ":%s: " in_context "\n",			\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
	} while (0)

#define	DEBUG_MODE		TRUE

#endif //NM_OTOOL_ERROR_H
