/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/06/27 14:47:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char *is_special(t_shell **shell, t_block *current, char *line, char *specials);
char *special_cases(t_shell **shell, t_block *current, char *line);

void args_matrix(t_block *current)
{
	t_cmd *current_cmd;
	int index;

	if (!current->commands)
		return ;
	index = -1;
	current_cmd = current->commands;
	current->args = (char **)ft_calloc(current->commands_n + 1, sizeof(char *));
	while (current_cmd && ++index < current->commands_n)
	{
		if (!index)
			current->cmd = ft_strtrim(current_cmd->arg, &current_cmd->quote);
		current->args[index] = current_cmd->arg;
		current_cmd = current_cmd->next;
	}
	current->args[index + 1] = NULL;
}

char	*is_var(t_shell **shell, t_block *current, char *line)
{
	t_env	*variable;
	char	*line_tmp;
	int		line_diff;

	line_tmp = line;
	if (!strcmp_mod(line_tmp, "$"))
	{
		line++;
		line_tmp++;
		while (*line_tmp && ft_isalnum_mod(*line_tmp))
			line_tmp++;
		line_diff = line_tmp - line;
		line = ft_substr(line, 0, line_diff);
		variable = find_arg(shell, line);
		if (variable == NULL)
		{
			printf("Cheguei aqui - IS NOT A VAR\n");
		// // 	current->current_var= ("NULL");
		// // 	printf("Cheguei aqui!\n");
		// // 	exit(1);
		}
		else
		{
			printf("Cheguei aqui - IS VAR\n");
			current->current_var = variable->msg;
		}
	}
	return (line_tmp);
}

char	*is_no_word(t_shell **shell, t_block *current, char *line)
{
	char *line_tmp;

	while (*line && line == is_special(shell, current, line, SPECIALS))
	{
		line_tmp = is_var(shell, current, line);
		if (line_tmp != line)
			return (line_tmp);
		if (*line == '\'' || *line == '\"')
		{
			current->quote = *line;
			while (*++line != current->quote)
			{
				line_tmp = is_var(shell, current, line);
				if (line_tmp != line)
					return (line_tmp);
				if (!*line)
					here_doc_exec(current, "\n");
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

/// @brief / Add node to the end of the list
/// @param list 		pointer to the list
/// @param node 		pointer to the node
void add_node(t_env **list, t_env *node)
{
	t_env	*temp;

	temp = *list;
	if (temp == NULL)
	{
		*list = node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
}

// void	print_list(t_env *list)
// {
// 	t_env	*temp;

// 	temp = list;
// 	while (temp != NULL)
// 	{
// 		printf("var: %s\n", temp->var);
// 		printf("msg: %s\n", temp->msg);
// 		temp = temp->next;
// 	}
// }

char *is_enviroment(t_shell **shell, char *line)
{
	char	*line_temp;
	char	*str_temp;
	t_env	*new_arg;
	int	i;
	int	k;

	line_temp = line;
	i = 0;
	k = 0;
	new_arg = (t_env *)ft_calloc(1, sizeof(t_env));
	if ((find(line_temp, '=')) == 1)
	{
		while(line_temp[i] != '=')
			i++;
		k = i;
		while((line_temp[k] != ' ' && line_temp[k] != '\0') || k == 0)
			k--;
		str_temp = ft_substr(line_temp, k + 1, i - k);
		str_temp = ft_substr(str_temp, 0, ft_strlen(str_temp) - 1);
		new_arg->var = str_temp;
		new_arg->msg = ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i);
		new_arg->type = 1;
		add_node(&(*shell)->env, new_arg);
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
		line = is_enviroment(shell, line);
		line = is_special(shell, current, line, SPECIALS);
		line = is_file_io(shell, current, line);
		(*shell)->line = line;
		line = is_command(shell, current, line);
		if (!*line || !current->set)
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

void	env_mtx_update(t_shell **shell, t_env *current, int env_n)
{
	char	**env_mtx;
	int		var_len;
	int		msg_len;

	if ((*shell)->env && (*shell)->paths_mtx)
		free_env_mtx((*shell)->env_mtx, env_n, (*shell)->paths_mtx, (*shell)->paths_n);
	(*shell)->env_mtx = (char **)ft_calloc(env_n + 1, sizeof(char *));
	env_mtx = (*shell)->env_mtx;
	while (current)
	{
		if (!strcmp_mod("PATH", current->var))
			(*shell)->paths_mtx = split_commands(shell, current->msg, ':');
		(*shell)->paths_n = (*shell)->count;
		var_len = strlen(current->var);
		msg_len = strlen(current->msg);
		*env_mtx = (char *)ft_calloc(var_len + msg_len + 2, sizeof(char));
		ft_strlcpy(*env_mtx, current->var, var_len + 1);
		ft_strlcpy(*env_mtx + var_len, "=", 2);
		ft_strlcpy(*env_mtx + var_len + 1, current->msg, msg_len + 1);
		*(env_mtx + var_len + msg_len) = '\0';
		current = current->next;
		env_mtx++;
	}
	env_mtx = NULL;
}

void	needs_env_update(t_shell **shell, t_env *current, int env_n)
{
	int	needs;

	needs = 0;
	needs += ((*shell)->env_mtx == NULL);
	if ((*shell)->pipelist)
	{
		needs += ((*shell)->pipelist->built_in == (void *)c_export);
		needs += ((*shell)->pipelist->built_in == (void *)c_unset);
	}
	if (needs)
		env_mtx_update(shell, current, env_n);
}

void minishell(t_shell **shell)
{
	char *line;

	signal_listener(SIG_IGN, handle_sigint);
	while (1)
	{
		printf("\033[1;35m");
		line = readline(make_text());
		(*shell)->exit_code = 0;
		if (line && *line)
		{
			needs_env_update(shell, (*shell)->env, (*shell)->env_n);
			add_history(line);
			pipe_list_build(shell, line);
			execution(shell, (*shell)->pipelist);
			// free_pipe_list(shell, (*shell)->pipelist);
		}
		else if (line == NULL)
			handle_sigquit(shell);
	}
}
