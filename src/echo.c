/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/06/21 13:43:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Passar norminette

void	c_echo(t_shell **shell)
{
	t_env	*node;

	shell = (shell);
	if ((*shell)->content && (*shell)->content[0] == '$')
	{
		node = find_arg(shell, ++(*shell)->content);
		if (node)
			printf("%s", node->msg);
	}
	else
		printf("%s", (*shell)->content);
	if (!(*shell)->flag || strcmp_mod((*shell)->flag, "-n"))
		printf("\n");
}
