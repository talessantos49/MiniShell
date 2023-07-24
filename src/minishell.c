/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by root              #+#    #+#             */
/*   Updated: 2023/07/24 03:16:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	manage_file_descriptors(t_block *current, char *file_name)
{
	if (current->set == 2 && current->fd[0])
		close(current->fd[0]);
	else if (current->set >= 3 && current->fd[1])
		close(current->fd[1]);
	if (current->set == 2)
		current->fd[0] = open(file_name, O_RDONLY, 0644);
	else if (current->set == 3)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (current->set == 4)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
}

char	*special_cases(t_shell **shell, t_block *current, char *line)
{
	if (*line == '<' && *++line)
	{
		current->set = 2;
		if (*line == '<' && *++line)
			return (here_doc_setup(shell, current, line));
	}
	else if (*line == '>' && *++line)
	{
		current->set = 3;
		if (*line == '>' && *++line)
			current->set = 4;
	}
	else if (*line == '|' && line++)
	{
		if (!pipe(current->pipe))
			current->set = 0;
	}
	return (line);
}

int	find(char *string1, char c)
{
	int		i;

	i = ft_strlen(string1);
	while (i >= 0)
	{
		if (string1[i] == c)
			return (1);
		i--;
	}
	return (0);
}

// char	*make_text(void)
// {
// 	char	*text;
// 	char	buf[1024];
// 	char	*path;
// 	char	*temp1;
// 	char	*temp2;

// 	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
// 	temp2 = ft_strjoin(temp1, getenv("USER"));
// 	free(temp1);
// 	temp1 = ft_strjoin("\033[1;33m", temp2);
// 	free(temp2);
// 	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
// 	free(temp1);
// 	path = getcwd(buf, 1024);
// 	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
// 	temp1 = ft_strjoin(temp2, path);
// 	free(path);
// 	free(temp2);
// 	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
// 	free(temp1);
// 	return (text);
// }

char	*make_text(t_shell **shell)
{
	char	*text;
	char	buf[1024];
	char	*path;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
	temp2 = ft_strjoin(temp1, getenv("USER"));
	free(temp1);
	temp1 = ft_strjoin("\033[1;33m", temp2);
	free(temp2);
	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
	free(temp1);
	if ((*shell)->actual_path == NULL
		|| (!(strcmp_mod((*shell)->actual_path, "HOME") == 0)))
		path = getcwd(buf, 1024);
	else
		path = (*shell)->actual_path;
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	temp1 = ft_strjoin(temp2, path);
	free(path);
	free(temp2);
	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp1);
	return (text);
}

void	minishell(t_shell **shell)
{
	char	*line;
	char	*prompt_text;

	prompt_text = make_text(shell);
	signal_listener(SIG_IGN, handle_sigint);
	(*shell)->actual_path = ft_strdup(getenv("HOME"));
	while (1)
	{
		free (prompt_text);
		prompt_text = make_text(shell);
		line = readline(prompt_text);
		(*shell)->exit_code = 0;
		if (line && *line)
		{
			needs_env_update(shell, (*shell)->env, (*shell)->env_n);
			add_history(line);
			pipe_list_build(shell, line);
			execution(shell, (*shell)->pipelist);
			free_pipe_list(shell, (*shell)->pipelist);
		}
		else if (line == NULL)
			handle_sigquit(shell);
	}
	free (prompt_text);
}
