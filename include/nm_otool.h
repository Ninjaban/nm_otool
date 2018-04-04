/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 08:46:10 by jcarra            #+#    #+#             */
/*   Updated: 2018/03/29 09:12:49 by jcarra           ###   ########.fr       */
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

typedef struct		s_types
{
	uint32_t		n_sect;
	char			type;
	void			*next;
}					t_types;

/*
**	ft_tools.c
*/
extern t_bool		ft_map_file(const int fd, const off_t size, t_buffer *file);
extern t_bool		ft_unmap_file(t_buffer *file);
extern t_bool		ft_magic_number(const char *path, t_buffer file);
extern t_bool		ft_check_addr(void *in_start, void *in_end, void *addr,
								uint32_t size);
extern t_bool		ft_get_type_free(t_types *types);

# define CHECK_ADDR(addr, size)		{ ft_check_addr(NULL, NULL, addr, size); }

# ifdef _MACHO_LOADER_H_

/*
**	ft_print.c
*/
extern char			ft_get_type(uint32_t n_sect, uint32_t n_type, t_types *types);
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
extern t_bool		ft_get_type64(struct load_command *lc, t_types **types);

/*
**	ft_print32.c
*/
extern t_bool		ft_get_type32(struct load_command *lc, t_types **types);
# endif

/*
**	ft_fat.c
*/
extern t_bool		ft_header_fat(t_buffer file);

#endif
