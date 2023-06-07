/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 00:44:55 by macarval          #+#    #+#             */
/*   Updated: 2022/04/30 19:30:39 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_str(const char *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!str[0])
		return (0);
	while (str[i] && str[i] == c)
		i++;
	while (*str)
	{
		if (*str != c && i == 0)
		{
			i = 1;
			len++;
		}
		else if (*str == c)
			i = 0;
		str++;
	}
	return (len);
}

static size_t	len_word(const char *str, char c, size_t len)
{
	size_t	tam;

	if (!str)
		return (1);
	tam = 0;
	while (str[len] != c && str[len])
	{
		tam++;
		len++;
	}
	return (tam);
}

static char	*ft_cpyword(const char *s, char c, size_t len)
{
	size_t	j;
	size_t	i;
	char	*str;

	j = 0;
	i = len_word(s, c, len);
	str = malloc ((i + 1) * sizeof(char));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (j < i)
	{
		str[j] = s[len + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	size_t	len;
	char	**str;

	j = 0;
	len = 0;
	if (!s)
		return (NULL);
	str = (char **) malloc ((size_str(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (j < size_str(s, c))
	{
		while (s[len] == c && s[len])
			len++;
		str[j] = ft_cpyword(s, c, len);
		j++;
		len += len_word(s, c, len);
	}
	str[j] = 0;
	return (str);
}
