/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/07/19 07:56:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

void	minishell(t_shell **shell)
{
	char	*line;

	signal_listener(SIG_IGN, handle_sigint);
	while (TRUE)
	{
		line = readline(COLOR_BHCYAN "MiniShell" COLOR_BHRED "$" \
		COLOR_BHCYAN "> " COLOR_RESET);
		(*shell)->exit_code = 0;
		if (line && *line)
		{
			add_history(line);
			pipe_list_build(shell, line);
			execution(shell, (*shell)->pipelist);
			free_pipe_list(shell, (*shell)->pipelist);
		}
		else if (line == NULL)
			handle_sigquit(shell);
	}
}
