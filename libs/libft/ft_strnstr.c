/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:18:56 by macarval          #+#    #+#             */
/*   Updated: 2022/07/07 21:59:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (ft_strlen(big) > ft_strlen(little))
	{
		while (big[i] && i < len)
		{
			j = 0;
			while (big[i + j] == little[j]
				&& little[j] && i + j < len)
				j++;
			if (j == ft_strlen(little))
				return ((char *)big + i);
			i++;
		}
	}
	return (0);
}
