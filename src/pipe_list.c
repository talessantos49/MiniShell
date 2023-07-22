/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:28:00 by root              #+#    #+#             */
/*   Updated: 2023/07/21 20:22:28 by root             ###   ########.fr       */
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

void	pipe_list_build(t_shell **shell, char *line)
{
	t_block	*current;
	t_cmd	*actual_cmd;

	current = NULL;
	while (line && *line)
	{
		if (!current || !current->set)
		{
			current = new_block_on_pipe_list(shell, current);
			(*shell)->pipelist->quote_position = (int *)malloc(sizeof(int));
			heredoc_name_setup(shell, current);
		}
		line = is_spaces(line, SPACES);
		// line = is_enviroment_definition(shell, line);
		// replace_word(line, "$?", ft_itoa((*shell)->exit_code));
		// line = change_enviroment(shell, line);
		printf("line[%s]\n", line);
		line = is_special(shell, current, line, SPECIALS);
		line = is_file_io(shell, current, line);
		(*shell)->line = line;
		line = is_command(shell, current, line);
		actual_cmd = current->current_command;
		// if (actual_cmd->quote != '\'')
		// if (actual_cmd->quote != '\'')
		// {
		// 	replace_word(actual_cmd->arg, "$?", ft_itoa((*shell)->exit_code));
		// 	actual_cmd->arg = change_enviroment(shell, actual_cmd->arg);
		// }
		if (actual_cmd->quote == '\'')
			actual_cmd->arg = ft_strip(actual_cmd->arg, '\'');
		else if (actual_cmd->quote == '\"')
		{
			replace_word(actual_cmd->arg, "$?", ft_itoa((*shell)->exit_code));
			actual_cmd->arg = change_enviroment(shell, actual_cmd->arg);
			actual_cmd->arg = ft_strip(actual_cmd->arg, '\"');
		}
		else
		{
			replace_word(actual_cmd->arg, "$?", ft_itoa((*shell)->exit_code));
			actual_cmd->arg = change_enviroment(shell, actual_cmd->arg);
		}
		if ((line && !*line) || !current->set)
			args_matrix(current);
		if (g_signal)
			break ;
	}
}
