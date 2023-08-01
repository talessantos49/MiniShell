/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:24:21 by root              #+#    #+#             */
/*   Updated: 2023/07/26 20:25:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	safe_free(void **ptr)
{
	unsigned char	**ptr_str;

	ptr_str = (unsigned char **)ptr;
	if (*ptr != NULL && **ptr_str != 0)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_shell(t_shell **shell)
{
	int	idx;

	while (idx < (*shell)->paths_n)
		free((*shell)->paths_mtx[idx++]);
	free_pipe_list(shell, (*shell)->pipelist);
}

void	free_pipe_list(t_shell **shell, t_block *current)
{
	t_block	*next;
	t_cmd	*next_cmd;
	t_cmd	*current_cmd;

	current_cmd = current->commands;
	safe_free((void **)&(*shell)->heredoc_name);
	while (current)
	{
		while (current_cmd)
		{
			next_cmd = current_cmd->next;
			safe_free((void **)&current_cmd->arg);
			safe_free((void **)&current_cmd);
			current_cmd = next_cmd;
		}
		unlink(current->heredoc_name);
		safe_free((void **)&current->cmd);
		safe_free((void **)&current->heredoc_name);
		next = current->next;
		safe_free((void **)&current);
		current = next;
		(*shell)->pid = 0;
	}
}

void	free_nodes(t_shell **shell)
{
	t_env	*aux;

	aux = NULL;
	while ((*shell)->env_n)
	{
		aux = (*shell)->env;
		(*shell)->env = (*shell)->env->next;
		free(aux->var);
		free(aux);
		(*shell)->env_n--;
	}
}

void	free_current(t_shell **shell)
{
	t_block	*aux;

	aux = (*shell)->pipelist;
	while (aux)
	{
		(*shell)->pipelist
			= (*shell)->pipelist->next;
		free(aux->heredoc_name);
		free(aux->current_var);
		free(aux->args);
		free(aux->cmd);
		free(aux->current_command->arg);
		free(aux->current_command);
		free(aux);
		aux = (*shell)->pipelist;
	}
}

void	exit_free(t_shell **shell)
{
	free_nodes(shell);
	free_pipe_list(shell, (*shell)->pipelist);
	free_current(shell);
	free_env_mtx((*shell)->env_mtx,
		(*shell)->env_n, (*shell)->paths_mtx, (*shell)->paths_n);
	exit((*shell)->exit_code);
}
