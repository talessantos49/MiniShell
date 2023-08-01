/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:28:00 by root              #+#    #+#             */
/*   Updated: 2023/07/26 12:46:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_block	*new_block_on_pipe_list(t_shell **shell, t_block *block_current)
{
	t_block	*pipe_block;

	pipe_block = (t_block *)ft_calloc(1, sizeof(t_block));
	pipe_block->set = 1;
	(*shell)->pipelist_n += 1;
	if (block_current)
	{
		pipe_block->fd[0] = block_current->pipe[0];
		block_current->next = pipe_block;
	}
	else if (!block_current)
		(*shell)->pipelist = pipe_block;
	return (pipe_block);
}

char	*black_box(t_shell **shell, t_block *current, char *line)
{
	line = is_spaces(line, SPACES);
	line = is_special(shell, current, line, SPECIALS);
	line = is_file_io(shell, current, line);
	(*shell)->line = line;
	line = is_command(shell, current, line);
	return (line);
}

void	cmd_quotes(t_shell **shell, t_block *current)
{
	t_cmd	*actual_cmd;
	char	*tmp;

	tmp = ft_itoa((*shell)->exit_code);
	actual_cmd = current->current_command;
	if (actual_cmd)
	{
		if (actual_cmd->quote == '\'')
			actual_cmd->arg = ft_strip(actual_cmd->arg, '\'');
		else if (actual_cmd->quote == '\"')
		{
			replace_word(actual_cmd->arg, "$?",
				tmp, 0);
			actual_cmd->arg = change_enviroment(shell, actual_cmd->arg, -1, 0);
			actual_cmd->arg = ft_strip(actual_cmd->arg, '\"');
		}
		else
		{
			replace_word(actual_cmd->arg, "$?",
				tmp, 0);
			actual_cmd->arg = change_enviroment(shell, actual_cmd->arg, -1, 0);
		}
	}
	free(tmp);
}

void	pipe_list_build(t_shell **shell, char *line)
{
	t_block	*current;

	current = NULL;
	while (line && *line)
	{
		if (!current || !current->set)
		{
			current = new_block_on_pipe_list(shell, current);
			heredoc_name_setup(shell, current);
		}
		line = black_box(shell, current, line);
		cmd_quotes(shell, current);
		if ((line && !*line) || !current->set)
			args_matrix(current);
		if (g_signal)
			break ;
	}
}

void	restore_std_io(int *std_io)
{
	dup2(std_io[0], STDIN_FILENO);
	close(std_io[0]);
	dup2(std_io[1], STDOUT_FILENO);
	close(std_io[1]);
}
