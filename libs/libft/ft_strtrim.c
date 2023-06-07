/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:46:52 by macarval          #+#    #+#             */
/*   Updated: 2022/04/29 21:54:49 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	init(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static size_t	final(char const *s1, char const *set)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = ft_strlen(s1) - 1;
	while (set[j] && k)
	{
		if (s1[k] == set[j])
		{
			k--;
			j = -1;
		}
		j++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		j;
	size_t		k;
	char		*str;

	j = 0;
	if (init(s1, set) >= ft_strlen(s1))
	{
		str = (char *) malloc (1 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	k = final(s1, set);
	str = (char *) malloc ((k - init(s1, set) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (init(s1, set) + j <= k)
	{
		str[j] = s1[init(s1, set) + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
