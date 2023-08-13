/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:28:00 by root              #+#    #+#             */
/*   Updated: 2023/07/19 16:19:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_file_descriptors(t_block *current, char *file_name)
{
	if (current->set == INFILE && current->fd[0])
		close(current->fd[0]);
	else if ((current->set == OUTFILE_NEW || current->set == OUTFILE_APPEND) \
	&& current->fd[1])
		close(current->fd[1]);
	if (current->set == INFILE)
		current->fd[0] = open(file_name, O_RDONLY, CHMOD);
	else if (current->set == OUTFILE_NEW)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, CHMOD);
	else if (current->set == OUTFILE_APPEND)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_APPEND, CHMOD);
}

void	new_command(t_block *current)
{
	current->commands_n += 1;
	if (!current->current_command)
	{
		current->current_command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		current->commands = current->current_command;
	}
	else if (current->commands)
	{
		current->current_command->next = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		current->current_command = current->current_command->next;
	}
}

t_block	*new_block_on_pipe_list(t_shell **shell, t_block *block_current)
{
	t_block	*pipe_block;

	pipe_block = (t_block *)ft_calloc(1, sizeof(t_block));
	pipe_block->set = COMMAND;
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

char	*special_cases(t_shell **shell, t_block *current, char *line)
{
	if (*line == '<' && *line++)
	{
		current->set = INFILE;
		if (*line == '<' && *line++)
			return (here_doc_setup(shell, current, line));
	}
	else if (*line == '>' && *line++)
	{
		current->set = OUTFILE_NEW;
		if (*line == '>' && *line++)
			current->set = OUTFILE_APPEND;
	}
	else if (*line == '|' && line++)
			current->set = NEW_BLOCK;
	return (line);
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
		line = is_spaces(line, STR_SPACES);
		line = is_special(shell, current, line, STR_SPECIALS);
		line = is_file_io(shell, current, line);
		line = is_spaces(line, STR_SPACES);
		line = is_command(shell, current, line);
		if (!line || (*shell)->exit_code)
			break;
		if ((line && !*line) || current->set == 0)
			execve_matrixes(shell, current);
	}
}
