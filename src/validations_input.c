/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:53:49 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:34:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*is_no_word(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;

	while (*line && line == is_special(shell, current, line, SPECIALS))
	{
		line_tmp = line;
		if (line_tmp != line)
			return (line_tmp);
		if (is_quote(current, *line))
		{
			while (*++line != current->quote)
			{
				if (!*line)
					return (quote_unclosed(current, line_tmp));
			}
			line++;
			break ;
		}
		else
			line++;
		if (line != is_spaces(line, SPACES))
			break ;
	}
	return (line);
}

char	*is_command(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;
	int		line_diff;

	line = is_spaces(line, SPACES);
	if (!*line || current->set != 1)
		return (line);
	current->set = 5;
	if (line != is_special(shell, current, line, SPECIALS))
	{
		current->set = 1;
		return (line);
	}
	line_tmp = line;
	line_tmp = is_no_word(shell, current, line_tmp);
	current->set = 1;
	line_diff = line_tmp - line;
	new_command(current);
	if (current->current_var && current->quote != '\'')
	{
		current->current_command->arg = current->current_var;
		current->current_var = NULL;
	}
	else
		current->current_command->arg = ft_substr(line, 0, line_diff);
	if (!current->commands->next)
		current->built_in = is_built_in(current->current_command->arg);
	return (line_tmp);
}

char	*is_file_io(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;
	char	*file_name;
	int		line_diff;

	if (current->set < 2 || current->set > 4)
		return (line);
	line = is_spaces(line, SPACES);
	line_tmp = line;
	line_tmp = is_no_word(shell, current, line_tmp);
	line_diff = line_tmp - line;
	if (current->current_var && current->quote != '\'')
		file_name = current->current_var;
	else
	file_name = ft_substr(line, 0, line_diff);
	manage_file_descriptors(current, file_name);
	current->set = 1;
	if (current->fd[0] < 0 || current->fd[1] < 0)
		return ("error file");
	return (line + line_diff);
}

char	*is_special(t_shell **shell,
	t_block *current, char *line, char *specials)
{
	while (*specials)
	{
		if (*line != *specials)
			specials++;
		else if (*line == *specials)
		{
			if (current->set == 5)
				return (line + 1);
			if (current->set == 2)
				return ("error token");
			return (special_cases(shell, current, line));
		}
	}
	return (line);
}

char	*is_spaces(char *line, char *spaces)
{
	while (*spaces)
	{
		if (*line != *spaces)
			spaces++;
		else if (*line == *spaces)
		{
			line++;
			spaces = SPACES;
		}
	}
	return (line);
}
