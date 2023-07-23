/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:31:09 by root              #+#    #+#             */
/*   Updated: 2023/07/22 22:43:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_node(t_env **list, t_env *node)
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

// void	remove_variable(t_env **list, t_env *node)
// {
// 	t_env	*temp;

// 	temp = *list;
// 	if (temp == NULL)
// 		return ;
// 	while (temp != NULL)
// 	{
// 		if (temp == node)
// 		{
// 			if (temp->prev == NULL)
// 			{
// 				*list = temp->next;
// 				if (temp->next)
// 					temp->next->prev = NULL;
// 			}
// 			else if (temp->next == NULL)
// 				temp->prev->next = NULL;
// 			else
// 			{
// 				temp->prev->next = temp->next;
// 				temp->next->prev = temp->prev;
// 			}
// 			free(temp->var);
// 			free(temp->msg);
// 			free(temp);
// 			return ;
// 		}
// 		temp = temp->next;
// 	}
// }

void	change_var(t_shell **shell, char *var, char *msg)
{
	t_env	*temp;

	temp = (*shell)->env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
		{
			free(temp->msg);
			temp->msg = ft_strdup(msg);
			return ;
		}
		temp = temp->next;
	}
}

void c_var_definition(t_shell **shell)
{
	char	*args;
	t_cmd	*temp_node;

	temp_node = (t_cmd *)ft_calloc(1, (sizeof(t_cmd)));
	temp_node = (*shell)->pipelist->commands;
	while (temp_node)
	{
		args = (temp_node->arg);
		if (find(args, '='))
			is_enviroment_definition(shell, args);
		temp_node = temp_node->next;
	}
}

// char	*is_enviroment_definition(t_shell **shell, char *line)
void	is_enviroment_definition(t_shell **shell, char *line)
{
	char	*line_temp;
	char	*str_temp;
	t_env	*new_arg;
	int		i;
	int		k;

	line_temp = line;
	i = 0;
	k = 0;
	new_arg = (t_env *)ft_calloc(1, sizeof(t_env));
	if ((find(line_temp, '=')) == 1)
	{
		while (line_temp[i] != '=')
			i++;
		k = i;
		while ((line_temp[k] != ' ' && line_temp[k] != '\0') || k == 0)
			k--;
		str_temp = ft_substr(line_temp, k + 1, i - k);
		str_temp = ft_substr(str_temp, 0, ft_strlen(str_temp) - 1);
		if (is_var(shell, str_temp))
			change_var(shell, str_temp, ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i));
		else
		{
			new_arg->len_var = ft_strlen(str_temp);
			new_arg->var = str_temp;
			new_arg->msg = ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i);
			new_arg->len_msg = ft_strlen(new_arg->msg);
			new_arg->next = NULL;
			(*shell)->env_n++;
			add_node(&(*shell)->env, new_arg);
		}
	}
}

// void	positions_and_values(t_shell **shell, int values, char *line, char character)
// {
// 	int	*positions = (int *)malloc(sizeof(int) * values);
// 	int	i;
// 	int	opened_quotes;
// 	int	closed_quotes;

// 	i = 0;
// 	opened_quotes = -1;
// 	closed_quotes = 0;
// 	values = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			if (opened_quotes == -1)
// 				opened_quotes = i;
// 			else
// 				closed_quotes = i;
// 		}
// 		if (opened_quotes != -1 && closed_quotes == 0)
// 		{
// 			if (line[i] == character)
// 			{
// 				positions[values] = i;
// 				values++;
// 				printf("positions[%d]: [%d]\n", values, positions[values - 1]);
// 			}
// 		}
// 		i++;
// 	}
// 	(*shell)->pipelist->quote_position = positions;
// 	return ;
// }

// int	counting_inside_quotes(t_shell **shell, char *line, char	character)
// {
// 	int	i;
// 	int	value;
// 	int	opened_quotes;
// 	int	closed_quotes;

// 	i = 0;
// 	value = 0;
// 	opened_quotes = -1;
// 	closed_quotes = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			if (opened_quotes == -1)
// 				opened_quotes = i;
// 			else
// 				closed_quotes = i;
// 		}
// 		if (opened_quotes != -1 && closed_quotes == 0)
// 		{
// 			if (line[i] == character)
// 				value++;
// 		}
// 		i++;
// 	}
// 	positions_and_values(shell, value, line, character);
// 	return (value);
// }

// int	inside_quotes(char	*str,char inside)
// {
// 	int	i;
// 	int	index_inside;
// 	int closed_quotes;
// 	int opened_quotes;

// 	i = 0;
// 	index_inside = 0;
// 	closed_quotes = 0;
// 	opened_quotes = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == inside)
// 			index_inside = i;
// 		if (str[i] == '\'')
// 		{
// 			if (opened_quotes == 0)
// 				opened_quotes = i;
// 			else
// 				closed_quotes = i;
// 		}
// 		if (opened_quotes != 0 && closed_quotes != 0)
// 		{
// 			if ((index_inside >= opened_quotes) && (index_inside <= closed_quotes))
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

char	*change_enviroment(t_shell **shell, char *line)
{
	char	*temp_line;
	char	*temp_variable;
	char	*searched_variable;
	t_env	*temp_node;
	int		i;
	int		k;
	// int		quotes_in;

	i = 0;
	temp_line = line;
	searched_variable = NULL;
	if (find(temp_line, '$'))
	{
		while (temp_line[i])
		{
			if (temp_line[i] == '$')
			{
				k = i + 1;
				while (temp_line[k] && temp_line[k] != ' '
					&& temp_line[k] != '$' && temp_line[k] != '\'' && temp_line[k] != '\"')
						k++;
				temp_variable = (char *)ft_calloc(k - i + 1, sizeof(char));
				if (find(temp_variable, ' '))
					k--;
				// if (temp_line[k] == '\"')
				temp_variable = ft_substr(temp_line, i + 1, k - i - 1);
				// else
				// 	temp_variable = ft_substr(temp_line, i + 1, k - i);
				temp_variable = ft_strip(temp_variable, ' ');
				temp_node = find_arg(shell, temp_variable);
				if (temp_node)
					searched_variable = temp_node->msg;
				else
				{
					temp_variable = ft_substr(temp_variable, 0, ft_strlen(temp_variable));
					temp_node = find_arg(shell, temp_variable);
					if (temp_node)
						searched_variable = temp_node->msg;
					else
						searched_variable = "";
				}
				temp_variable = ft_strjoin("$", temp_variable);
				replace_word(temp_line, temp_variable, searched_variable);
			}
			i++;
		}
	}
	(*shell)->exit_code = 0;
	return (temp_line);
}

void	replace_word(char *sentence, const char *word_replace,
			const char *replacement)
{
	char	*found_word;
	char	*new_sentence;
	size_t	word_replace_len;
	size_t	replacement_len;
	size_t	new_sentence_len;
	int		offset;

	found_word = strstr(sentence, word_replace);
	if (found_word != NULL)
	{
		word_replace_len = ft_strlen(word_replace);
		replacement_len = ft_strlen(replacement);
		offset = replacement_len - word_replace_len;
		new_sentence_len = ft_strlen(sentence) + offset + 1;
		new_sentence = malloc(new_sentence_len);
		if (new_sentence == NULL)
		{
			printf("Erro ao alocar memória\n");
			return ;
		}
		strncpy(new_sentence, sentence, found_word - sentence);
		new_sentence[found_word - sentence] = '\0';
		strcat(new_sentence, replacement);
		strcat(new_sentence, found_word + word_replace_len);
		strcpy(sentence, new_sentence);
		free(new_sentence);
	}
}

// void replaceWord(char* sentence, const char* wordToReplace, const char* replacement)
// {
//     char* foundWord = strstr(sentence, wordToReplace);
//     if (foundWord != NULL)
//     {
//         size_t wordToReplaceLength = strlen(wordToReplace);
//         size_t replacementLength = strlen(replacement);

//         int offset = replacementLength - wordToReplaceLength;
//         size_t newSentenceLength = strlen(sentence) + offset + 1;

//         // Aloca memória para a nova string
//         char* newSentence = malloc(newSentenceLength);
//         if (newSentence == NULL)
//         {
//             printf("Erro ao alocar memória\n");
//             return;
//         }

//         // Copia a parte da string antes da palavra a ser substituída
//         strncpy(newSentence, sentence, foundWord - sentence);
//         newSentence[foundWord - sentence] = '\0';

//         // Concatena a substituição na nova string
//         strcat(newSentence, replacement);

//         // Concatena a parte da string após a palavra a ser substituída
//         strcat(newSentence, foundWord + wordToReplaceLength);

//         // Copia a nova string de volta para a string original
//         strcpy(sentence, newSentence);

//         // Libera a memória alocada
//         free(newSentence);
//     }
// }