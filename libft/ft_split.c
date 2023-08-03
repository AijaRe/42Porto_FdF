/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:34:27 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/14 17:34:30 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_limit(char const *str, char delim)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	return (i);
}

static int	count_strs(char const *s, char c)
{
	size_t	i;
	size_t	len;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		len = ft_strlen_limit(s + i, c);
		i += len;
		if (len > 0)
			n++;
	}
	return (n);
}

static void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

/*allocate memory for pointers to each new string*/
/*keeps iterating until finds new separator or end of string*/
/*when the condition above is true, outputs string*/
/*ft condition: add last NULL string*/
char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	int		num;
	char	**new;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	num = count_strs(s, c);
	new = (char **)malloc(sizeof(char *) * (num + 1));
	if (!new)
		return (NULL);
	while (++j < num)
	{
		while (s[i] == c)
			i++;
		new[j] = ft_substr(s, i, ft_strlen_limit(s + i, c));
		if (!new[j])
			return (free_tab(new));
		i += ft_strlen_limit(s + i, c);
	}
	new[num] = NULL;
	return (new);
}
