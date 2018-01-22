/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:16:38 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/21 13:05:07 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_next(t_btree **tree, t_btree **next, void *item)
{
	if (*next)
	{
		*tree = *next;
		return (0);
	}
	else
	{
		*next = (t_btree *)item;
		return (1);
	}
}

void		btree_add_node(t_btree **root, void *item,
						int (*cmpf)(void *, void *))
{
	t_btree	*tree;
	int		exit;

	if (!root || !item || !cmpf)
		return ;
	exit = (!(*root)) ? 1 : 0;
	tree = *root;
	if (!(*root))
		*root = (t_btree *)item;
	while (exit == 0)
	{
		if (cmpf(tree, item) < 0)
			exit = ft_next(&tree, &tree->left, item);
		else
			exit = ft_next(&tree, &tree->right, item);
	}
}
