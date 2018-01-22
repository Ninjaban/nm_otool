/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:18:32 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/30 13:36:01 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ESC_H
# define FT_ESC_H

/*
** special characters
**
** $ 0x24, ` 0x60, \ 0x5c, ! 0x21, * 0x2a, @ 0x40
**
** \a 0x07, \b 0x08, \e 0x1b, \f 0x0c, \n 0x0a, \r 0x0d, \t 0x09, \v 0x0b
**  \ 0x5c,  ' 0x27,  " 0x22,  ? 0x3f
**
** \c CTRL, \cx CTRL + x
** \nnn octal, \xHH hex, \uHHHH unicode, \UHHHHHHHH unicode
*/

# define SIZE 4096

# define ANSI_MAX 12

# define ANSI_C_CHAR "abefnrtv\\\'\"\?"
# define ANSI_C_1 0x07, 0x08, 0x1b, 0x0c, 0x0a, 0x0d, 0x09, 0x0b
# define ANSI_C_2 0x5c, 0x27, 0x22, 0x3f
# define ANSI_LIST (char [ANSI_MAX]){ANSI_C_1, ANSI_C_2}

# define IS_ESC_1(x) (x == 0x07 || x == 0x08 || x == 0x1b || x == 0x0c)
# define IS_ESC_2(x) (x == 0x0a || x == 0x0d || x == 0x09 || x == 0x0b)
# define IS_ESC_3(x) (x == 0x5c || x == 0x27 || x == 0x22 || x == 0x3f)
# define IS_ESC(x) (IS_ESC_1(x) || IS_ESC_2(x) || IS_ESC_3(x))

# define IS_ANSI_1(x) (x == 'a' || x == 'b' || x == 'e' || x == 'f')
# define IS_ANSI_2(x) (x == 'n' || x == 'r' || x == 't' || x == 'v')
# define IS_ANSI_3(x) (x == 0x5c || x == 0x27 || x == 0x22 || x == 0x3f)
# define IS_ANSI(x) (IS_ANSI_1(x) || IS_ANSI_2(x) || IS_ANSI_3(x))

# define IS_ESC_NB(x) ((x == 'x') || (x == 'u') || (x == 'U'))
# define ESC_NB "xuU"
# define ESC_NB_S (size_t [3]){2, 4, 8}

/*
** Eval struct
*/

typedef struct	s_eval
{
	char	*res;
	char	*tmp;
	size_t	n_tmp;
	char	buf[SIZE + 1];
	int		n_buf;
}				t_eval;

/*
** Functions
*/

void			ft_esc_c(t_eval *e);
void			ft_esc_hex(t_eval *e);
char			ft_esc_x(char *token, size_t *n);
char			*ft_eval(char *str);

#endif
