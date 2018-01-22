/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:04:45 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:15:40 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_c(char c, char const *check)
{
	size_t	n;

	n = 0;
	while (check[n] && check[n] == c)
		n = n + 1;
	if (!check[n])
		return (1);
	return (0);
}

static int	count_word(char const *s, char const *c)
{
	int		n;
	int		word;

	n = 0;
	word = 0;
	while (check_c(s[n], c) == 1 && s[n])
		n = n + 1;
	while (s[n])
	{
		word = word + 1;
		while (s[n] && check_c(s[n], c) == 0)
			n = n + 1;
		while (check_c(s[n], c) == 1 && s[n])
			n = n + 1;
	}
	return (word);
}

static int	size_word(char const *s, char const *c, int n)
{
	int		len;

	len = 0;
	while (s[n + len] && check_c(s[n + len], c) == 0)
		len = len + 1;
	return (len);
}

static char	**complete_tab(char const *s, char const *c, char **tab)
{
	int		n;
	int		i;
	int		j;

	n = 0;
	i = 0;
	while (check_c(s[n], c) == 1 && s[n])
		n = n + 1;
	while (s[n])
	{
		if ((tab[i] = malloc(size_word(s, c, n) + 1)) == NULL)
			return (NULL);
		j = 0;
		while (s[n] && check_c(s[n], c) == 0)
			tab[i][j++] = s[n++];
		tab[i++][j] = '\0';
		while (check_c(s[n], c) == 1 && s[n])
			n = n + 1;
	}
	return (tab);
}

char		**ft_explode(char const *s, char const *c)
{
	char	**tab;
	int		word;

	if (s == NULL || c == NULL)
		return (NULL);
	word = count_word(s, c);
	if ((tab = malloc(sizeof(char *) * (word + 1))) == NULL)
		return (NULL);
	while (word >= 0)
		tab[word--] = NULL;
	if ((tab = complete_tab(s, c, tab)) == NULL)
		return (NULL);
	return (tab);
}
