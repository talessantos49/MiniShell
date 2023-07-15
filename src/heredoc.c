/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:21:30 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:22:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	signal_handle(char *delimiter)
{
	if (g_signal == SIGQUIT)
	{
		ft_putstr_fd(HDSIGQUIT1, STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd(HDSIGQUIT2, STDERR_FILENO);
	}
	if (g_signal)
		return (1);
	return (0);
}

void	heredoc_name_setup(t_shell **shell, t_block *current)
{
	if (!(*shell)->heredoc_name)
		(*shell)->heredoc_name = ft_substr(HEREDOCNAME, 0, 6);
	else if ((*shell)->heredoc_name)
	{
		if ((*shell)->heredoc_name[5] == '9')
		{
			(*shell)->heredoc_name[5] = '0';
			(*shell)->heredoc_name[4] += 1;
		}
		(*shell)->heredoc_name[5] += 1;
	}
	current->heredoc_name = ft_substr((*shell)->heredoc_name, 0, 6);
}

void	here_doc_exec(t_block *current, char *delimiter)
{
	char	*heredoc_name;
	char	*user_input;
	int		user_input_len;

	heredoc_name = current->heredoc_name;
	current->fd[0] = open(heredoc_name, O_CREAT | O_RDWR, 0644);
	signal_listener(signal_set, signal_set);
	while (1)
	{
		user_input = readline("> ");
		user_input_len = ft_strlen(user_input);
		if (g_signal || !strcmp_mod(user_input, delimiter))
			break ;
		write(current->fd[0], user_input, user_input_len);
		write(current->fd[0], "\n", 1);
	}
	close(current->fd[0]);
	if (signal_handle(delimiter))
		return ;
	current->fd[0] = open(heredoc_name, O_RDONLY);
}

char	*here_doc_setup(t_shell **shell, t_block *current, char *line)
{
	char	*line_tmp;
	int		line_diff;
	char	*delimiter;

	current->set = 3;
	line = is_spaces(line, SPACES);
	line_tmp = line;
	line_tmp = is_no_word(shell, current, line_tmp);
	current->set = 1;
	line_diff = line_tmp - line;
	delimiter = ft_substr(line, 0, line_diff);
	here_doc_exec(current, delimiter);
	return (line + line_diff);
}
