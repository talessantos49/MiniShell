/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:13:21 by macarval          #+#    #+#             */
/*   Updated: 2022/04/28 00:24:44 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*n;

	p = *lst;
	while (p != NULL)
	{
		n = p->next;
		del(p->content);
		free(p);
		p = n;
	}
	*lst = NULL;
}
