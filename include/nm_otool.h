/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:46:10 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/20 12:54:38 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

enum	e_array
{
	ARRAY_FAT,
	ARRAY_32,
	ARRAY_64
};

/*
**	ft_tools.c
*/
extern t_bool		ft_map_file(const int fd, const off_t size, t_buffer *file);
extern t_bool		ft_unmap_file(t_buffer *file);
extern t_bool		ft_magic_number(const char *path, t_buffer file,
									t_bool (*f[3])(t_buffer));
extern t_bool		ft_check_addr(void *in_start, void *in_end, void *addr,
								uint32_t size);

# define CHECK_ADDR(addr, size)		{ ft_check_addr(NULL, NULL, addr, size); }

# ifdef _MACHO_LOADER_H_

/*
**	ft_print.c
*/
extern char			ft_get_type(uint32_t n_sect, uint32_t n_type,
		struct load_command *lc, char (*f)(uint32_t, struct load_command *));
# endif

/*
**	ft_header64.c
*/
extern t_bool		ft_header_64(t_buffer file);

/*
**	ft_header32.c
*/
extern t_bool		ft_header_32(t_buffer file);

# ifdef _MACHO_LOADER_H_

/*
**	ft_print64.c
*/
extern char			ft_get_type64(uint32_t n_sect, struct load_command *lc);

/*
**	ft_print32.c
*/
extern char			ft_get_type32(uint32_t n_sect, struct load_command *lc);
# endif

/*
**	ft_fat.c
*/
extern t_bool		ft_header_fat(t_buffer file);

#endif
