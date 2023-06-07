/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:07:57 by macarval          #+#    #+#             */
/*   Updated: 2022/04/29 05:08:33 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*p;

	if (size > 2147483647)
		return (NULL);
	p = (void *)malloc(number * size);
	if (!p)
		return (NULL);
	ft_bzero(p, number * size);
	return (p);
}
