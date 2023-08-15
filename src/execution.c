/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:57:08 by root              #+#    #+#             */
/*   Updated: 2023/08/15 19:53:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	wait_children(t_shell **shell, t_block *current)
{
	int	status;

	status = 0;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			(*shell)->exit_code = WEXITSTATUS(status);
		current = current->next;
	}
}

void	close_pipes(t_shell **shell, t_block *current)
{
	if (current != (*shell)->pipelist)
		close((*shell)->previous->pipe[0]);
	if (current->next)
		close(current->pipe[1]);
}

static void	pipeline_manager(t_shell **shell, t_block *current)
{
	if (current->fd[1])
	{
		dup2(current->fd[1], STDOUT_FILENO);
		close(current->fd[1]);
	}
	else if (current->pipe[1])
	{
		dup2(current->pipe[1], STDOUT_FILENO);
		close(current->pipe[0]);
	}
	if (current->fd[0])
	{
		dup2(current->fd[0], STDIN_FILENO);
		close(current->fd[0]);
	}
	else if (*shell && (*shell)->previous && (*shell)->previous->pipe[0])
		dup2((*shell)->previous->pipe[0], STDIN_FILENO);
}

static void	child(t_shell **shell, t_block *current)
{
	int8_t	exit_code;

	exit_code = (*shell)->exit_code;
	signal_handled_exec(shell);
	pipeline_manager(shell, current);
	if (current->built_in)
	{
		current->built_in(shell);
		if (!is_env_bultins(current->built_in, current->next))
		{
			free_shell(shell);
			exit(exit_code);
		}
	}
	else if (execve(current->cmd, current->args, (*shell)->env_mtx) < 0)
	{
		perror(current->cmd);
		free_shell(shell);
		exit(-1);
	}
}

void	execution(t_shell **shell, t_block *current)
{
	while (!(*shell)->exit_code && current && current->cmd)
	{
		if (current->next)
			pipe(current->pipe);
		if (!current->built_in && command_validate(shell, current))
		{
			current = current->next;
			continue ;
		}
		signal_listener(NULL, SIG_IGN);
		if (!is_env_bultins(current->built_in, current->next))
			current->pid = fork();
		if (!current->pid)
			child(shell, current);
		close_pipes(shell, current);
		(*shell)->previous = current;
		current = current->next;
	}
	wait_children(shell, (*shell)->pipelist);
}
