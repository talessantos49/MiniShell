/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 03:19:49 by macarval          #+#    #+#             */
/*   Updated: 2022/04/21 01:27:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*r;
	const char	*s;

	i = 0;
	r = dst;
	s = src;
	while (i < len)
	{
		r[i] = s[i];
		i++;
	}
	dst = r;
	return (dst);
}
