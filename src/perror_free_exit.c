/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_free_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:24:21 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:27:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	restore_std_io(int *std_io)
{
	dup2(std_io[0], STDIN_FILENO);
	close(std_io[0]);
	dup2(std_io[1], STDOUT_FILENO);
	close(std_io[1]);
}

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

void	perror_free(char *type, char *name)
{
	int	name_len;
	int	type_len;

	name_len = ft_strlen(name);
	type_len = ft_strlen(type);
	write(2, name, name_len);
	write(2, type, type_len);
	write(2, "\n", 1);
}

void	error(char *msg, t_shell **shell, int free_type, int exit_code)
{
	ft_putstr_fd(msg, 2);
	if (free_type)
		free_shell(shell);
	if (exit_code)
	{
		free_shell(shell);
		exit(exit_code);
	}
}
