/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/02/23 19:10:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
