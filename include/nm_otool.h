//
// Created by Nathan on 30/01/18.
//

#ifndef NM_OTOOL_NM_OTOOL_H
# define NM_OTOOL_NM_OTOOL_H

/*
**	ft_tools.c
*/
extern t_bool		ft_map_file(const int fd, const off_t size, t_buffer *file);
extern t_bool		ft_unmap_file(t_buffer *file);
extern t_bool		ft_magic_number(const char *path, t_buffer file,
									 void (f)(t_buffer));

/*
**	ft_print.c
*/
extern char			ft_nsect_decription(uint32_t n_sect, uint32_t n_type);
extern uint32_t		*ft_get_order(uint32_t nsyms, char *stringtable,
									 struct nlist_64 *list);

#endif