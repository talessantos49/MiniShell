/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:11:31 by root              #+#    #+#             */
/*   Updated: 2023/07/24 01:11:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_node(t_env **list, t_env *node)
{
	t_env	*temp;

	temp = *list;
	if (temp == NULL)
	{
		*list = node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
}

void	change_var(t_shell **shell, char *var, char *msg)
{
	t_env	*temp;

	temp = (*shell)->env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
		{
			free(temp->msg);
			temp->msg = ft_strdup(msg);
			return ;
		}
		temp = temp->next;
	}
}

void	c_var_definition(t_shell **shell)
{
	char	*args;
	t_cmd	*temp_node;

	temp_node = (t_cmd *)ft_calloc(1, (sizeof(t_cmd)));
	temp_node = (*shell)->pipelist->commands;
	while (temp_node)
	{
		args = (temp_node->arg);
		if (find(args, '='))
			is_enviroment_definition(shell, args, 0, 0);
		temp_node = temp_node->next;
	}
}

t_env	*node_atribuition(char *var, char *msg)
{
	t_env	*new_arg;

	new_arg = (t_env *)ft_calloc(1, sizeof(t_env));
	new_arg->len_var = ft_strlen(var);
	new_arg->var = var;
	new_arg->len_msg = ft_strlen(msg);
	new_arg->msg = msg;
	new_arg->next = NULL;
	return (new_arg);
}
