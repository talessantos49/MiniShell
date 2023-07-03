/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/06/10 20:49:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char *is_special(t_shell **shell, t_block *current, char *line, char *specials);
char *special_cases(t_shell **shell, t_block *current, char *line);

void quote_clean(t_block *current, char *command, char quote)
{
	char *quote_ptr;

	current->cmd = ft_strtrim(command, &quote);
	quote_ptr = current->cmd;
	while (quote_ptr)
	{
		quote_ptr = ft_strchr(quote_ptr, quote);
		if (!quote_ptr || !*quote_ptr)
			break;	
		quote_ptr[0] = 1;
		quote_ptr += 1;
	}
}

void args_matrix(t_block *current)
{
	t_cmd	*current_cmd;
	int		index;

	if (!current->commands)
		return ;
	index = -1;
	current_cmd = current->commands;
	current->args = (char **)ft_calloc(current->commands_n, sizeof(char *));
	while (current_cmd && ++index < current->commands_n)
	{
		if (!index)
			quote_clean(current, current_cmd->arg, current_cmd->quote);		
		current->args[index] = current_cmd->arg;
		current_cmd = current_cmd->next;
	}
	current->args[index + 1] = NULL;
}

// char	*is_var(t_shell **shell, t_block *current, char *line)
// {
// 	char	*line_tmp;
// 	int		line_diff;

// 	line_tmp = line;
// 	if (*line_tmp == '$')
// 	{
// 		line++;
// 		line_tmp++;
// 		while (*line_tmp && ft_isalnum_mod(*line_tmp))
// 			line_tmp++;
// 		line_diff = line_tmp - line;
// 		line = ft_substr(line, 0, line_diff);
// 		// variable = find_arg(shell, line);
// 		// if (variable == NULL)
// 		// {
// 		// 	printf("Cheguei aqui - IS VAR\n");
// 		// // // 	current->current_var= ("NULL");
// 		// // // 	printf("Cheguei aqui!\n");
// 		// // // 	exit(1);
// 		// }
// 		// else
// 		// 	current->current_var = variable->msg;
// 	}
// 	return (line_tmp);
// }

void new_command(t_block *current)
{
	current->commands_n += 1;
	if (!current->current_command)
	{
	    current->current_command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		current->current_command->quote = current->quote;
		current->commands = current->current_command;
	}
	else if (current->commands)
	{
		current->current_command->next = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		current->current_command->next->quote = current->quote;
		current->current_command = current->current_command->next;
	}
	current->quote = 0;
}

char *quote_append(char **current, char* append, int newline)
{
	char	*new;
	char	*new_appd;
	int		appd_len;
	int		crrt_len; 

	if (!*current)
		*current = "";
	crrt_len = ft_strlen(*current);
	appd_len = ft_strlen(append);
	new = (char *)ft_calloc((crrt_len + appd_len) + newline, sizeof(char));
	new_appd = new + crrt_len + newline;
	ft_strlcpy(new, *current, (crrt_len + appd_len) + 1);
	ft_strlcpy(new_appd - 1, "\n", (newline * 2));
	ft_strlcpy(new_appd, append, appd_len + 1);
	safe_free((void **)current);
	return (new);
}

int quote_nested(char *string, char quote)
{
	char	*quote_pair;

	while (*string)
	{
		quote_pair = ft_strchr(string, quote);
		quote_pair = ft_strchr(quote_pair + 1, quote);
		if (!quote_pair)
			return (1);
		else
			string = quote_pair + 1;
	}
	return (0);
}


char *quote_unclosed(t_block *current, char *input)
{
	char	**final_str;
	char	*quote_break;
	
	quote_break = NULL;
	new_command(current);
    signal_listener(signal_set, handle_sigint);
	final_str = &current->commands->arg;
	*final_str = quote_append(&current->commands->arg, input, 0);
	while (1 && !quote_break)
	{
		input = readline("> ");
		*final_str = quote_append(&current->commands->arg, input, 1);
		if (quote_nested(input, current->current_command->quote))
			break;
	}
	add_history(*final_str);
	return ("\0");
}

int	 is_quote(t_block *current, char line)
{
	if (line == '\'')
		current->quote = '\'';
	else if (line == '\"')
		current->quote = '\"';
	else
		return (0);
	return (1);
}

char	*is_no_word(t_shell **shell, t_block *current, char *line)
{
	char *line_tmp;

	while (*line && line == is_special(shell, current, line, SPECIALS))
	{
		line_tmp = line; // line_tmp = is_var(shell, current, line);
		if (line_tmp != line)
			return (line_tmp);
		if (is_quote(current, *line))
		{
			while (*++line != current->quote)
			{
				if (!*line)
					return (quote_unclosed(current, line_tmp));
				// line_tmp = is_var(shell, current, line);
			}
			line++;
			break; 
		}
		else
			line++;
		if (line != is_spaces(line, SPACES))
			break;
	}
	return (line);
}


char *is_command(t_shell **shell, t_block *current, char *line)
{
	char *line_tmp;
	int	line_diff;

	line = is_spaces(line, SPACES);
	if (!*line || current->set != 1 )
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
	return(line_tmp);
}

void manage_file_descriptors(t_block *current, char *file_name)
{
	if (current->set == 2 && current->fd[0])
		close(current->fd[0]);
	else if (current->set >= 3 && current->fd[1])
		close(current->fd[1]);
	if (current->set == 2)
		current->fd[0] = open(file_name, O_RDONLY);
	else if (current->set == 3)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (current->set == 4)
		current->fd[1] = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
}

char *is_file_io(t_shell **shell, t_block *current, char *line)
{
	char *line_tmp;
	char *file_name;
	int	line_diff;

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
		return("error file");
	return(line + line_diff);
} 



char *special_cases(t_shell **shell, t_block *current, char *line)
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
		if(!pipe(current->pipe))
			current->set = 0;
	}
	return (line);
}

char *is_special(t_shell **shell, t_block *current, char *line, char *specials)
{
	while (*specials)
	{
		if (*line != *specials)
			specials++;
		else if (*line == *specials)
		{
			if (current->set == 5)
				return(line + 1);
			if (current->set == 2)
				return ("error token");
			return (special_cases(shell, current, line));
		}
	}
	return (line); 
}


char *is_spaces(char *line, char *spaces)
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

void pipe_list_build(t_shell **shell, char *line)
{
	t_block *current;

	current = NULL;
	while (line && *line)
	{
		if (!current || !current->set)
		{
			current = new_block_on_pipe_list(shell, current);
			heredoc_name_setup(shell, current);
		}
		line = is_spaces(line, SPACES);
		line = is_special(shell, current, line, SPECIALS);
		line = is_file_io(shell, current, line);
		line = is_command(shell, current, line);
		if ((line && !*line) || !current->set)
				args_matrix(current);
		if (g_signal)
			break;
	}
}

char	*make_text(void)
{
	char	*text;
	char	buf[256];
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
	path = getcwd(buf, 256);
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	temp1 = ft_strjoin(temp2, path);
	free(path);
	free(temp2);
	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp1);
	return (text);
}

void	free_env_mtx(char **env, int env_n, char **paths, int paths_n)
{
	char **env_tmp;
	int idx;

	idx = -1;
	env_tmp = env;
	while (++idx < env_n)
	{
		safe_free((void **)&*env_tmp);
		env_tmp++;
	}
	safe_free((void **)&env);
	idx = -1;
	env_tmp = paths;
	while (++idx < paths_n)
	{
		safe_free((void **)&*env_tmp);
		env_tmp++;
	}
	safe_free((void **)&paths);
}

void minishell(t_shell **shell)
{
	char *line;
	
	signal_listener(SIG_IGN, handle_sigint);
	while (1)
	{
		line = readline(make_text());
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
