/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:18:11 by macarval          #+#    #+#             */
/*   Updated: 2022/04/29 05:34:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*r;
	unsigned char	l;
	size_t			i;

	i = 0;
	l = (unsigned char) c;
	r = (unsigned char *) b;
	while (i < len)
	{
		if (*r == l)
			return (r);
		i++;
		r++;
	}
	return (NULL);
}
