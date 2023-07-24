/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:46:47 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:59:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	free_split(char ***split)
// {
// 	int		i;
// 	char	**temp;

// 	i = -1;
// 	temp = *split;
// 	while (temp[++i])
// 		free(temp[i]);
// 	free(*split);
// }

t_env	*find_arg(t_shell **shell, char *var)
{
	t_env	*temp;

	temp = (*shell)->env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	args_matrix(t_block *current)
{
	t_cmd	*current_cmd;
	int		index;

	if (!current->commands)
		return ;
	index = -1;
	current_cmd = current->commands;
	current->args = (char **)ft_calloc(current->commands_n + 1, sizeof(char *));
	while (current_cmd && ++index < current->commands_n)
	{
		if (!index)
			quote_clean(current, current_cmd->arg, current_cmd->quote);
		current->args[index] = current_cmd->arg;
		current_cmd = current_cmd->next;
	}
	current->args[index + 1] = NULL;
}
