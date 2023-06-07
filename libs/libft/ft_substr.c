/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:32:52 by macarval          #+#    #+#             */
/*   Updated: 2022/04/29 21:45:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (start > ft_strlen(s))
	{
		res = (char *) malloc(1 * sizeof(char));
		if (!res)
			return (NULL);
		res [0] = '\0';
		return (res);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	res = (char *) malloc (sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
