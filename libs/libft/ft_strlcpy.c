/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:23:48 by macarval          #+#    #+#             */
/*   Updated: 2022/04/21 01:29:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{	
	size_t	len;
	size_t	control;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (dstsize)
	{
		if (dstsize > len)
			control = len;
		else
			control = dstsize - 1;
		while (i < control)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}	
	return (len);
}
