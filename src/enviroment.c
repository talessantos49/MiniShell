/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:31:09 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:02:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	is_enviroment_definition(t_shell **shell, char *line, int i, int k)
{
	char	*line_temp;
	char	*str_temp;
	t_env	*new_arg;

	line_temp = line;
	new_arg = (t_env *)ft_calloc(1, sizeof(t_env));
	if ((find(line_temp, '=')) == 1)
	{
		while (line_temp[i] != '=')
			i++;
		k = i;
		while ((line_temp[k] != ' ' && line_temp[k] != '\0') || k == 0)
			k--;
		str_temp = ft_substr(line_temp, k + 1, i - k - 1);
		if (is_var(shell, str_temp))
			change_var(shell, str_temp, ft_substr
				(line_temp, i + 1, ft_strlen(line_temp) - i));
		else
		{
			new_arg = node_atribuition(str_temp, ft_substr
					(line_temp, i + 1, ft_strlen(line_temp) - i));
			(*shell)->env_n++;
			add_node(&(*shell)->env, new_arg);
		}
	}
}

char	*change_enviroment(t_shell **shell, char *line, int i, int k)
{
	char	*temp_line;
	char	*temp_variable;
	t_env	*temp_node;

	temp_line = line;
	while (temp_line[++i])
	{
		if (temp_line[i] == '$')
		{
			k = i + 1;
			while (temp_line[k] && temp_line[k] != ' ' && temp_line[k]
				!= '$' && temp_line[k] != '\'' && temp_line[k] != '\"')
					k++;
			temp_variable = (char *)ft_calloc(k - i + 1, sizeof(char));
			temp_variable = ft_substr(temp_line, i + 1, k - i - 1);
			temp_variable = ft_strip(temp_variable, ' ');
			temp_node = find_arg(shell, temp_variable);
			temp_variable = ft_strjoin("$", temp_variable);
			if (temp_node)
				replace_word(temp_line, temp_variable, temp_node->msg, 0);
			else
				replace_word(temp_line, temp_variable, "", 0);
			free(temp_variable);
		}
	}
	return (temp_line);
}

void	replace_word(char *string, const char *word_replace,
				const char *replacement, int offset)
{
	char	*found_word;
	char	*new_sentence;
	size_t	word_replace_len;
	size_t	replacement_len;
	size_t	new_sentence_len;

	found_word = strstr(string, word_replace);
	if (found_word != NULL)
	{
		word_replace_len = ft_strlen(word_replace);
		replacement_len = ft_strlen(replacement);
		offset = replacement_len - word_replace_len;
		new_sentence_len = ft_strlen(string) + offset + 1;
		new_sentence = malloc(new_sentence_len);
		if (new_sentence == NULL)
			return ;
		strncpy(new_sentence, string, found_word - string);
		new_sentence[found_word - string] = '\0';
		strcat(new_sentence, replacement);
		strcat(new_sentence, found_word + word_replace_len);
		strcpy(string, new_sentence);
		free(new_sentence);
	}
}
