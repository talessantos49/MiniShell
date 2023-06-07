/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:27:35 by macarval          #+#    #+#             */
/*   Updated: 2022/04/21 01:29:29 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < count)
		i++;
	while (count > 0 && (i + j) < (count - 1) && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (j > 0)
		dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
