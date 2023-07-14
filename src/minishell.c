/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/07/10 14:30:06 by root             ###   ########.fr       */
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
	current->args = (char **)ff_calloc(current->commands_n, sizeof(char *));
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
	    current->current_command = (t_cmd *)ff_calloc(1, sizeof(t_cmd));
		current->current_command->quote = current->quote;
		current->commands = current->current_command;
	}
	else if (current->commands)
	{
		current->current_command->next = (t_cmd *)ff_calloc(1, sizeof(t_cmd));
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

size_t	ft_strlcpy_open(char *dst, const char *src, size_t dstsize)
{	
	size_t	len;
	size_t	control;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (dstsize)
	{
		if (dstsize > len)
			control = len;
		else
			control = dstsize - 1;
		while (i < control)
		{
			dst[i] = src[i];
			i++;
		}
	}	
	return (len);
}

void replaceWord(char* sentence, const char* wordToReplace, const char* replacement) {
    char* foundWord = strstr(sentence, wordToReplace);
    if (foundWord != NULL) {
        size_t wordToReplaceLength = strlen(wordToReplace);
        size_t replacementLength = strlen(replacement);

        int offset = replacementLength - wordToReplaceLength;
        size_t newSentenceLength = strlen(sentence) + offset + 1;

        // Aloca memória para a nova string
        char* newSentence = malloc(newSentenceLength);
        if (newSentence == NULL) {
            printf("Erro ao alocar memória\n");
            return;
        }

        // Copia a parte da string antes da palavra a ser substituída
        strncpy(newSentence, sentence, foundWord - sentence);
        newSentence[foundWord - sentence] = '\0';

        // Concatena a substituição na nova string
        strcat(newSentence, replacement);

        // Concatena a parte da string após a palavra a ser substituída
        strcat(newSentence, foundWord + wordToReplaceLength);

        // Copia a nova string de volta para a string original
        strcpy(sentence, newSentence);

        // Libera a memória alocada
        free(newSentence);
    }
}

// void replaceWord(char* sentence, const char* wordToReplace, const char* replacement) {
//     char* foundWord = strstr(sentence, wordToReplace);
//     if (foundWord != NULL) {
//         size_t wordToReplaceLength = strlen(wordToReplace);
//         size_t replacementLength = strlen(replacement);

//        ft_memmove(foundWord + replacementLength, foundWord + wordToReplaceLength, ft_strlen(foundWord + wordToReplaceLength) + 1);
//     	ft_memcpy(foundWord, replacement, replacementLength);
//     }
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// void replaceWord(char* sentence, const char* wordToReplace, const char* replacement) {
//     char* foundWord = strstr(sentence, wordToReplace);
//     if (foundWord != NULL) {
//         size_t wordToReplaceLength = strlen(wordToReplace);
//         size_t replacementLength = strlen(replacement);

//         // Calcula o deslocamento necessário para a substituição
//         int offset = replacementLength - wordToReplaceLength;

//         // Calcula o novo tamanho da string
//         size_t newSentenceLength = strlen(sentence) + offset + 1;

//         // Aloca memória para a nova string
//         char* newSentence = malloc(newSentenceLength);

//         // Copia a parte da string antes da palavra a ser substituída
//         strncpy(newSentence, sentence, foundWord - sentence);
//         newSentence[foundWord - sentence] = '\0';

//         // Concatena a substituição na nova string
//         strcat(newSentence, replacement);

//         // Concatena a parte da string após a palavra a ser substituída
//         strcat(newSentence, foundWord + wordToReplaceLength);

//         // Atualiza a string original com a nova string
//         strcpy(sentence, newSentence);

//         // Libera a memória alocada
//         free(newSentence);
//     }
// }

// int main() {
//     char sentence[] = "echo teste1 $? teste2";
//     char wordToReplace[] = "$?";
//     char replacement[] = "10";

//     printf("Antes: %s\n", sentence);
//     replaceWord(sentence, wordToReplace, replacement);
//     printf("Depois: %s\n", sentence);

//     return 0;
// }



char *replace_string(char *string, char *src, char *dest)
{
	char	*temp_string;
	int		string_len;
	int		src_len;
	int		dest_len;
	char	*teste;
	int		i;
	int		k;
	int		len_total;

	teste=string;
	string_len = ft_strlen(string);
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	len_total = string_len - src_len + dest_len + 1;
	printf("len_total = %d\n", len_total);
	i = 0;
	k = 0;
	temp_string = (char *)calloc(string_len - src_len + dest_len + 1, sizeof(char));
	// printf("temp_string = %s\n", temp_string);  TEM QUE LIDAR COM OS PROBLEMAS DE CONTINUAÇÃO DA STRING ---PRECISA VERIFICAR.
	// printf("in string_len = %d\n", string_len);
	// printf("in string = %s\n", string);
	// printf("in temp_string = %s\n", temp_string);
	while (string[i] || i < string_len)
	{
		if (string[i] == src[0])
		{
			if (ft_strncmp(&string[i], src, src_len) == 0)
			{
				while (dest[k])
				{
					temp_string[i + k] = dest[k];
					k++;
				}
				i += src_len;
				k = 0;
			}
			else
				temp_string[i + k] = string[i];
		}
		else
		{
			temp_string[i + k] = string[i];
			printf("string = %s\t", string);
			printf("temp_string = %s\t", temp_string);
			printf("[%d]\n", i);
		}
		i++;
	}
	temp_string[i + k] = '\0';
	// printf("out temp_string_len = %ld\n", ft_strlen(temp_string));
	// printf("out string_len = %d\n", string_len);
	// printf("out string = %s\n", string);
	printf("out temp_string = %s\n", temp_string);
	// printf("-----------------------\n");
	replaceWord(teste, src, dest);
	printf("out teste = %s\n", teste);
	return (temp_string);
}

char *change_enviroment(t_shell **shell, char *line)
{
	char	*temp_line;
	char	*temp_variable;
	char	*searched_variable;
	t_env	*temp_node;
	int		i;
	int		k;

	i = 0;
	temp_line = line;
	if (find(temp_line, '$'))
	{
		while (temp_line[i])
		{
			if (temp_line[i] == '$')
			{
				k = i + 1;
				while (temp_line[k] && temp_line[k] != ' ' && temp_line[k] != '$')
					k++;
				temp_variable = (char *)calloc(k - i + 1, sizeof(char));
				temp_variable = ft_substr(temp_line, i + 1, k - i);
				temp_node = find_arg(shell, temp_variable);
				if (temp_node)
					searched_variable = temp_node->msg;
				else
					searched_variable = "";
				temp_variable = ft_strjoin("$", temp_variable);
				replaceWord(temp_line, temp_variable, searched_variable);
				// temp_line = replace_string(temp_line, temp_variable, searched_variable);
			}
			i++;
		}
	}
	(*shell)->exit_code = 0;
	return (temp_line);
}

char *is_enviroment_definition(t_shell **shell, char *line)
{
	char	*line_temp;
	char	*str_temp;
	t_env	*new_arg;
	int	i;
	int	k;

	line_temp = line;
	i = 0;
	k = 0;
	new_arg = (t_env *)ff_calloc(1, sizeof(t_env));
	if ((find(line_temp, '=')) == 1)
	{
		while(line_temp[i] != '=')
			i++;
		k = i;
		while((line_temp[k] != ' ' && line_temp[k] != '\0') || k == 0)
			k--;
		str_temp = ft_substr(line_temp, k + 1, i - k);
		str_temp = ft_substr(str_temp, 0, ft_strlen(str_temp) - 1);
		new_arg->len_var = ft_strlen(str_temp);
		new_arg->var = str_temp;
		new_arg->msg = ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i);
		new_arg->len_msg = ft_strlen(new_arg->msg);
		new_arg->type = 1;
		add_node(&(*shell)->env, new_arg);
	}
	return (line);
}

// void pipe_list_build(t_shell **shell, char *line)
// {
// 	t_block *current;
// 	char	**splited_line;
// 	int		i;
// 	char	*temp_line;

// 	current = NULL;
// 	printf("line: %s\n", line);
// 	(*shell)->parser = (t_parser *)ff_calloc(1, sizeof(t_parser));
// 	i = 1;
// 	if (find(line, '|'))
// 		printf("pipe found\n");
// 	else
// 	{
// 		if (find(line, ' '))
// 			splited_line= ft_split(line, ' ');
// 		else
// 			printf("no space found\n");
// 		(*shell)->parser->command = splited_line[0];
// 		if (find(splited_line[1], '-'))
// 			(*shell)->parser->flag = splited_line[1];
// 		while (splited_line[i + 1])
// 		{
// 			temp_line = ft_strjoin(splited_line[i], " ");
// 			temp_line = ft_strjoin(temp_line, splited_line[i + 1]);
// 			printf("temp_line: %s\n", temp_line);
// 			i++;
// 		}
// 		(*shell)->parser->content = splited_line[2];
// 		printf("parser->command: %s\n", (*shell)->parser->command);
// 		printf("parser->flag: %s\n", (*shell)->parser->flag);
// 		printf("parser->content: %s\n", (*shell)->parser->content);
// 	}
// 	// (*shell)->line1 = is_command(shell, current, (*shell)->line1);
// 	// (*shell)->line1 = is_spaces((*shell)->line1, SPACES);
// 	while (line && *line)
// 	{
// 		if (!current || !current->set)
// 		{
// 			current = new_block_on_pipe_list(shell, current);
// 			heredoc_name_setup(shell, current);
// 		}
// 		// printf("shell line : %s\n", (*shell)->line1);
// 		line = is_spaces(line, SPACES);
// 		line = is_enviroment(shell, line);
// 		line = is_special(shell, current, line, SPECIALS);
// 		line = is_file_io(shell, current, line);
// 		(*shell)->line = line;
// 		line = is_command(shell, current, line);
// 		if (!*line || !current->set)
// 				args_matrix(current);
// 		if (g_signal)
// 			break;
// 	}
// }

void pipe_list_build(t_shell **shell, char *line)
{
	t_block *current;
	// char	**splited_line;
	// char	**splited_pipes;
	// int		i;
	// int		k;
	// char	*temp_line;

	current = NULL;
	// printf("line: %s\n", line);
	// (*shell)->parser = (t_parser *)ff_calloc(1, sizeof(t_parser));
	// (*shell)->parser->command = NULL;
	// (*shell)->parser->flag = NULL;
	// (*shell)->parser->content = NULL;
	// i = 1;
	// k = 0;
	// if (find(line, '|'))
	// {
	// 	printf("pipe found\n");
	// 	splited_pipes = ft_split(line, '|');
	// 	while (splited_pipes[k])
	// 	{
	// 		i = 1;
	// 		if (find(splited_pipes[k], ' '))
	// 		{
	// 			splited_line= ft_split(splited_pipes[k], ' ');
	// 			(*shell)->parser->command = splited_line[0];
	// 			if (find(splited_line[i], '-'))
	// 				(*shell)->parser->flag = splited_line[i++];
	// 			while (splited_line[i + 1])
	// 			{
	// 				temp_line = ft_strjoin(splited_line[i], " ");
	// 				temp_line = ft_strjoin(temp_line, splited_line[i + 1]);
	// 				splited_line[i + 1] = temp_line;
	// 				printf("[%d- splited_line: %s]\n",i,  splited_line[i]);
	// 				i++;
	// 			}
	// 			(*shell)->parser->content = splited_line[i];
	// 			// ("splited_line[%d]: %s\n", i, splited_line[i]);
	// 			// (*shell)->parser->content = splited_line[2];
	// 			printf("parser->command: %s\n", (*shell)->parser->command);
	// 			printf("parser->flag: %s\n", (*shell)->parser->flag);
	// 			printf("parser->content: %s\n", (*shell)->parser->content);
	// 			(*shell)->parser->next = (t_parser *)ff_calloc(1, sizeof(t_parser));
	// 			(*shell)->parser = (*shell)->parser->next;
	// 		}
	// 		else
	// 			printf("no space found\n");
	// 		// printf("Separou por aqui\n");
	// 		k++;
	// 	}
	// }
	// else
	// 	if (find(line, ' '))
	// 	{
	// 		line = ft_strtrim(line, " ");
	// 		if (find(line, ' '))
	// 		{
	// 			// line = ft_strtrim(line, " ");
	// 			// if (find(line, ' '))
	// 			splited_line= ft_split(line, ' ');
	// 			// else
	// 				// (*shell)->parser->command = line;
	// 		}
	// 		else
	// 			(*shell)->parser->command = line;
	// 			// printf("no space inside found\n");
	// 		// (*shell)->parser->command = splited_line[0];
	// 		if (find(splited_line[1], '-'))
	// 			(*shell)->parser->flag = splited_line[i++];
	// 		while (splited_line[i + 1])
	// 		{
	// 			temp_line = ft_strjoin(splited_line[i], " ");
	// 			temp_line = ft_strjoin(temp_line, splited_line[i + 1]);
	// 			splited_line[i + 1] = temp_line;
	// 			i++;
	// 		}
	// 		if ((*shell)->parser->command == NULL)
	// 		{
	// 			(*shell)->parser->command = splited_line[0];
	// 		}
	// 		if (find(line, ' '))
	// 			(*shell)->parser->content = splited_line[i];
	// 		// ("splited_line[%d]: %s\n", i, splited_line[i]);
	// 		// (*shell)->parser->content = splited_line[2];a
	// 		printf("parser->command: %s\n", (*shell)->parser->command);
	// 		printf("parser->flag: %s\n", (*shell)->parser->flag);
	// 		printf("parser->content: %s\n", (*shell)->parser->content);
	// 	}
	// 	else
	// 	{
	// 		printf("no space found\n");
	// 		(*shell)->parser->command = ft_strjoin(line, "\0");
	// 		printf("parser->command: %s\n", (*shell)->parser->command);
	// 		printf("parser->flag: %s\n", (*shell)->parser->flag);
	// 		printf("parser->content: %s\n", (*shell)->parser->content);
	// 	}
	// (*shell)->parser->command = is_enviroment_definition(shell, (*shell)->parser->command);
	
	while (line && *line)
	{
		if (!current || !current->set)
		{
			current = new_block_on_pipe_list(shell, current);
			heredoc_name_setup(shell, current);
		}
		line = is_spaces(line, SPACES);
		line = is_enviroment_definition(shell, line);
		replaceWord(line, "$?", ft_itoa((*shell)->exit_code));
		// line = replace_string(line, "$?", ft_itoa((*shell)->exit_code));
		printf("line: %s\n", line);
		line = change_enviroment(shell, line);
		line = is_special(shell, current, line, SPECIALS);
		line = is_file_io(shell, current, line);
		(*shell)->line = line;
		// printf("line: %s\n", line);
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
	(*shell)->env_mtx = (char **)ff_calloc(env_n, sizeof(char *));
	env_mtx = (*shell)->env_mtx;
	while (current)
	{
		if (!strcmp_mod("PATH", current->var))
			(*shell)->paths_mtx = split_commands(shell, current->msg, ':');
		(*shell)->paths_n = (*shell)->count;
		var_len = strlen(current->var);
		msg_len = strlen(current->msg);
		*env_mtx = (char *)ff_calloc(var_len + msg_len + 2, sizeof(char));
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
