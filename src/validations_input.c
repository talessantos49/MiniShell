/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:53:49 by root              #+#    #+#             */
/*   Updated: 2023/07/17 12:51:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_io_valid_token(int set, char line, char *newline, char *str_void)
{
	if (set >= 2 && set <= 4 && (!line || ft_strchr(STR_SPECIALS, line)))
	{
		if (!line)
			line = 1;
		else
			newline = str_void;
		ft_printfd(ERROR_IO_CHAR, STDERR_FILENO, newline, line);
		return (EXCEPTION);
	}
	return (SUCCES);
}

char	*is_no_word(t_shell **shell, t_block *current, char *line)
{
	if (is_io_valid_token(current->set, *line, STR_NEWLINE, STR_VOID))
		return (NULL);
	current->arg_0 = line;
	while (line == is_special(shell, current, line, STR_SPECIALS))
	{
		if (current->set != TEST_HEREDOC && line != is_quote(current, line))
		{
			is_var(shell, current, line, 0);
			while (*++line != current->current_quote->quote && *line)
				is_var(shell, current, line, 0);
			if (!*line)
			{
				current->current_quote->quote = 0;
				current->quotes_n -= 1;
			}
		}
		is_var(shell, current, line, 0);
		if (!*line || line != is_spaces(line, STR_SPACES))
			break;
		line++;
	}
	return (line);
}

char	*is_command(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;

	if (!line || !*line || current->set != COMMAND)
		return (line);
	current->set = TEST_HEREDOC;
	if (line != is_special(shell, current, line, STR_SPECIALS))
	{
		current->set = COMMAND;
		return (line);
	}
	current->set = COMMAND;
	line_tmp = is_no_word(shell, current, line);
	new_command(current);
	if (current->expand)
		current->current_command->arg = current->expand;
	else
		current->current_command->arg = ft_substr(line, 0, (line_tmp - line));
	if (current->quotes_list && current->quotes_list->quote)
		current->current_command->arg = quotes_clean(current, \
	&current->current_command->arg, ft_strlen(current->current_command->arg));
	current->expand = NULL;
	if (!current->commands->next)
		current->built_in = is_built_in(current->current_command->arg);
	return (line_tmp);
}

char	*is_file_io(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;
	char	*file_name;

	if (!line || current->set < INFILE || current->set > OUTFILE_APPEND)
		return (line);
	line = is_spaces(line, STR_SPACES);
	line_tmp = is_no_word(shell, current, line);
	if (!line_tmp)
		return (NULL);
	if (current->expand)
		file_name = current->expand;
	else
		file_name = ft_substr(line, 0, (line_tmp - line));
	if (current->quotes_list && current->quotes_list->quote)
		file_name = quotes_clean(current, &file_name, ft_strlen(file_name));
	current->expand = NULL;
	manage_file_descriptors(current, file_name);
	if (current->fd[0] < 0 || current->fd[1] < 0)
	{
		ft_printfd(ERROR_FD_DIR, STDERR_FILENO, file_name);
		return (NULL);
	}
	current->set = COMMAND;
	return (line_tmp);
}

char	*is_special(t_shell **shell, \
t_block *current, char *line, char *specials)
{
	while (*specials)
	{
		if (*line && *line != *specials)
			specials++;
		else if (!*line || *line == *specials)
		{
			if (current->set == TEST_HEREDOC)
				return (line + 1);
			return (special_cases(shell, current, line));
		}
	}
	return (line);
}

char	*is_spaces(char *line, char *spaces)
{
	while (line && *spaces)
	{
		if (*line != *spaces)
			spaces++;
		else if (*line == *spaces)
		{
			line++;
			spaces = STR_SPACES;
		}
	}
	return (line);
}

void	is_var(t_shell **shell, t_block *current, char *arg, int arg_len)
{
	t_env	*var;

	if (current->set == TEST_HEREDOC || (current->current_quote \
	&& current->current_quote->quote == CHAR_Q_SINGLE))
		return ; 
	if (*arg == CHAR_VAR || (current->expand \
	&& (arg != is_spaces(arg, STR_SPACES) || !*arg || *arg == CHAR_EQUAL \
	|| (current->current_quote && *arg == current->current_quote->quote))))
	{
		arg_len = (arg - current->arg_0);
		if (current->arg_0[0] == CHAR_VAR && (arg - current->arg_0) > 1)
		{
			var = find_var(shell, current->arg_0 + 1, arg_len - 1, 0);
			current->arg_0 = NULL;
			arg_len = 0;
			if (var)
				current->arg_0 = var->value;
			if (var && var->value)
				arg_len = ft_strlen(var->value);
		} 
		current->arg_0 = ft_substr(current->arg_0, 0, arg_len);
		current->expand = ft_strjoin(current->expand, current->arg_0);
		safe_free(&current->arg_0);
		current->arg_0 = arg;
	}
}
