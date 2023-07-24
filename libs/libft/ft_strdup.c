/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:48:33 by bluiz-al          #+#    #+#             */
/*   Updated: 2023/07/23 22:52:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cache;
	char	*ptr;

	cache = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	ptr = cache;
	while (*s)
		*cache++ = *(char *)s++;
	return (ptr);
}
