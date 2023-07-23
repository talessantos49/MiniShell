/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:49:18 by root              #+#    #+#             */
/*   Updated: 2023/07/23 19:56:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	c_env(t_shell **shell)
{
	int		var_len;
	int		msg_len;
	t_env	*temp;

	shell = (shell);
	temp = (*shell)->env;
	if (!is_flag_null(shell, ""))
		return ;
	while (temp != NULL)
	{
		// if (temp->type != LOCAL && temp->msg)
		if (temp->msg)
		{
			var_len = ft_strlen(temp->var);
			msg_len = ft_strlen(temp->msg);
			write(1, temp->var, var_len);
			write(1, "=", 1);
			write(1, temp->msg, msg_len);
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

t_env	*insert_front(t_env *new, char *var, char *msg, int type)
// t_env	*insert_front(t_env *new, char *var, char *msg)
{
	t_env	*node;

	node = (t_env *) malloc (sizeof (t_env));
	if (!node)
		return (0);
	node->var = NULL;
	node->msg = NULL;
	node->type = type;
	if (var)
		node->var = ft_strdup(var);
	if (msg)
		node->msg = ft_strdup(msg);
	node->prev = NULL;
	node->next = new;
	if (new != NULL)
		new->prev = node;
	free(var);
	return (node);
}

void	insert_last(t_env **env, t_env *new)
{
	t_env	*list;

	if (!env)
		return ;
	if (*env)
	{
		list = *env;
		while (list->next != NULL)
			list = list->next;
		list->next = new;
		new->prev = list;
	}
	else
		*env = new;
}

// t_env	*make_list(t_shell **shell, char **envp)
// {
// 	t_env	*env;
// 	t_env	*node;

// 	env = NULL;
// 	while (*envp)
// 	{
// 		node = NULL;
// 		node = insert_front(node,
// strchr_rev(*envp, '='), 
// 		strchr_mod(*envp, '='), ENVP);
// 		insert_last(&env, node);
// 		envp++;
// 		(*shell)->env_n++;
// 	}
// 	return (env);
// }

t_env	*make_list(t_shell **shell, char **envp)
{
	t_env	*env;
	t_env	*node;

	env = NULL;
	while (*envp)
	{
		node = NULL;
		node = insert_front(node, strchr_rev(*envp, '='), \
		strchr_mod(*envp, '='), ENVP);
		// strchr_mod(*envp, '='));
		insert_last(&env, node);
		envp++;
		(*shell)->env_n++;
	}
	return (env);
}
