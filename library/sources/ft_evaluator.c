/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:50:07 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/07 15:31:10 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

static void	ft_update_token(t_eval *eval, char **token)
{
	eval->res = ft_strjoin(*token, eval->buf);
	free(*token);
	*token = eval->res;
	eval->tmp += eval->n_tmp;
	eval->n_buf = 0;
	eval->n_tmp = 0;
	ft_memset((void *)(eval->buf), 0, SIZE + 1);
}

void		ft_eval_default(t_eval *e, char **token, char *str)
{
	e->tmp = str;
	while (*(e->tmp))
	{
		while (e->tmp[e->n_tmp] && e->n_buf < SIZE)
		{
			if (e->tmp[e->n_tmp] == 0x5c)
			{
				ft_update_token(e, token);
				ft_esc_c(e);
			}
			else
				e->buf[e->n_buf] = e->tmp[e->n_tmp];
			if (e->tmp[e->n_tmp])
				e->n_tmp++;
			e->n_buf++;
		}
		if (!(e->tmp[e->n_tmp]) || e->n_buf == SIZE)
			ft_update_token(e, token);
	}
}

static void	ft_init_eval(t_eval *eval)
{
	eval->res = NULL;
	eval->tmp = NULL;
	eval->n_tmp = 0;
	ft_memset((void *)(eval->buf), '\0', SIZE + 1);
	eval->n_buf = 0;
}

char		*ft_eval(char *str)
{
	char	*token;
	t_eval	eval;

	if ((token = (char *)ft_memalloc(sizeof(char))) == NULL)
		return (NULL);
	ft_init_eval(&eval);
	ft_eval_default(&eval, &token, str);
	return (token);
}
