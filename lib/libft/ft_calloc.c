/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:29:39 by bluiz-al          #+#    #+#             */
/*   Updated: 2023/07/23 22:50:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	int		result;
	void	*s;

	result = nmemb * size;
	if (result == 0 || result / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(result);
	s = ptr;
	while (result--)
		*(unsigned char *)s++ = 0;
	return (ptr);
}
