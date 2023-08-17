/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_free_exit2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:06:08 by root              #+#    #+#             */
/*   Updated: 2023/08/16 16:29:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_around(t_block *current_cmd)
{
	t_cmd	*next_cmd;
	t_cmd	*current;

	next_cmd = ft_calloc(1, sizeof(t_cmd));
	current = current_cmd->commands;
	while (current)
	{
		next_cmd = current->next;
		safe_free(&current);
		current = next_cmd;
	}
}

void	free_pipe_list(t_shell **shell, t_block *current)
{
	t_block	*next;
	t_cmd	*current_cmd;

	if (current)
		current_cmd = current->commands;
	else
		return ;
	if (current_cmd && current->cmd != current_cmd->arg)
		safe_free(&current->cmd);
	(*shell)->pipelist_n = 0;
	(*shell)->previous = NULL;
	while (current)
	{
		free_args_matrix(current, current->args);
		safe_free(&current->args);
		unlink(current->heredoc_name);
		safe_free(&(*shell)->heredoc_name);
		if (current_cmd)
			free_around(current);
		next = current->next;
		safe_free(&current);
		(*shell)->pipelist = NULL;
		current = next;
	}
}

// void	free_pipe_list(t_shell **shell, t_block *current)
// {
// 	t_block	*next;
// 	t_cmd	*current_cmd;
// 	t_cmd	*next_cmd;

// 	if (current)
// 		current_cmd = current->commands;
// 	else
// 		return ;
// 	if (current_cmd && current->cmd != current_cmd->arg)
// 		safe_free(&current->cmd);
// 	while (current)
// 	{
// 		free_args_matrix(current, current->args);
// 		safe_free(&current->args);
// 		unlink(current->heredoc_name);
// 		safe_free(&(*shell)->heredoc_name);
// 		while (current_cmd)
// 		{
// 			next_cmd = current_cmd->next;
// 			safe_free(&current_cmd);
// 			current_cmd = next_cmd;
// 		}
// 		next = current->next;
// 		safe_free(&current);
// 		(*shell)->pipelist = NULL;
// 		current = next;
// 	}
// }