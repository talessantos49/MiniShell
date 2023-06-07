/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:34:36 by macarval          #+#    #+#             */
/*   Updated: 2022/04/21 01:27:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;
	char	*r;

	i = 0;
	r = dest;
	while (i < len)
	{
		r[i] = c;
		i++;
	}
	dest = r;
	return (dest);
}
