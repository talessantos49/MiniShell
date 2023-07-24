/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:02:11 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:12:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_export(t_shell **shell)
{
	t_env	*temp;

	temp = (*shell)->env;
	while (temp != NULL)
	{
		if (temp->type == ENVP)
		{
			printf("declare -x %s", temp->var);
			if (temp->msg)
				printf("=\"%s\"", temp->msg);
			printf("\n");
		}
		temp = temp->next;
	}
}

void	c_export(t_shell **shell)
{
	t_cmd	*temp_node;

	temp_node = (*shell)->pipelist->commands;
	if (temp_node->next == NULL)
		print_export(shell);
}
