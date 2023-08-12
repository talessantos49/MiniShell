/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:57:08 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:13:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int is_env_bultins(void *builtin, t_block *arg)
{
	if ((builtin == c_export && !arg) || builtin == c_unset \
	|| builtin == c_exit || builtin == c_cd)
		return (TRUE);
	return (FALSE);
}


void	wait_children(t_shell **shell, t_block *current)
{
	int status;

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

void	pipeline_manager(t_shell **shell, t_block *current)
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
	else if ((*shell)->previous)
		dup2((*shell)->previous->pipe[0], STDIN_FILENO);
}

void	child(t_shell **shell, t_block *current)
{
	signal_handled_exec(shell);
	pipeline_manager(shell, current);
	if (current->built_in)
	{
		current->built_in(shell);
		if (!is_env_bultins(current->built_in, current->next))
			exit((*shell)->exit_code);
	}
	else if (execve(current->cmd, current->args, (*shell)->env_mtx) < 0)
	{
		perror(current->cmd);
		exit(-1);
	}
}

int is_file_or_directory(char *arg)
{
	char	buf[BUF];
	char	*cwd_backup;

	cwd_backup = getcwd(buf, BUF);
	if (ft_strchr(arg, *STR_SLASH))
	{
		if (chdir(arg))
			ft_printfd(ERROR_FD_DIR, STDERR_FILENO, arg);
		else
			ft_printfd(ERROR_IS_DIR, STDERR_FILENO, arg);
		chdir(cwd_backup);
		return (TRUE);
	}
	return(FALSE);
}

int	command_validate(t_shell **shell, t_block *current)
{
	char	*cmd_tmp;
	char	*cmd_tmp2;
	int		i;

	i = -1;
	if (is_file_or_directory(current->cmd))
		return (EXCEPTION);
	while (*current->cmd && ++i < (*shell)->paths_n)
	{
		cmd_tmp = ft_strjoin((*shell)->paths_mtx[i], STR_SLASH);
		cmd_tmp2 = ft_strjoin(cmd_tmp, current->cmd);
		safe_free(&cmd_tmp);
		if (!(access(current->args[0], X_OK)) || !(access(cmd_tmp2, X_OK)))
		{
			if (!(access(current->args[0], X_OK)))	
				current->cmd = ft_strdup(current->args[0]);
			else
				current->cmd = cmd_tmp2;
			return (SUCCES);
		}
		else
			safe_free(&cmd_tmp2);
	}
	ft_printfd(ERROR_CMD, STDERR_FILENO, current->cmd);
	return (EXCEPTION);
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
