/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:29:34 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:40:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	remove_variable(t_shell **shell, t_env **list, char *var)
{
	t_env	*temp_node;

	temp_node = *list;
	if (temp_node == NULL)
		return ;
	while (temp_node != NULL)
	{
		if (!strcmp_mod(temp_node->var, var))
		{
			if (temp_node->prev == NULL)
			{
				*list = temp_node->next;
				if (temp_node->next)
					temp_node->next->prev = NULL;
			}
			else if (temp_node->next == NULL)
				temp_node->prev->next = NULL;
			else
			{
				temp_node->prev->next = temp_node->next;
				temp_node->next->prev = temp_node->prev;
			}
			(*shell)->env_n--;
			return ;
		}
		temp_node = temp_node->next;
	}
}

void	c_unset(t_shell **shell)
{
	if (is_var(shell, (*shell)->pipelist->commands->next->arg))
	{
		if ((*shell)->pipelist->commands->next->arg)
		{
			remove_variable(shell, &(*shell)->env,
				(*shell)->pipelist->commands->next->arg);
		}
	}
	(*shell)->exit_code = 0;
}
