/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:31:09 by root              #+#    #+#             */
/*   Updated: 2023/07/15 19:41:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
		new_arg->len_var = ft_strlen(str_temp);
		new_arg->var = str_temp;
		new_arg->msg = ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i);
		new_arg->len_msg = ft_strlen(new_arg->msg);
		new_arg->type = 1;
		add_node(&(*shell)->env, new_arg);
	}
	return (line);
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
				{
					temp_variable = ft_substr(temp_variable, 0, ft_strlen(temp_variable) - 1);
					temp_node = find_arg(shell, temp_variable);
					if (temp_node)
						searched_variable = temp_node->msg;
					else
						searched_variable = "";
				}
				temp_variable = ft_strjoin("$", temp_variable);
				replaceWord(temp_line, temp_variable, searched_variable);
			}
			i++;
		}
	}
	(*shell)->exit_code = 0;
	return (temp_line);
}

void replaceWord(char* sentence, const char* wordToReplace, const char* replacement)
{
    char* foundWord = strstr(sentence, wordToReplace);
    if (foundWord != NULL)
    {
        size_t wordToReplaceLength = strlen(wordToReplace);
        size_t replacementLength = strlen(replacement);

        int offset = replacementLength - wordToReplaceLength;
        size_t newSentenceLength = strlen(sentence) + offset + 1;

        // Aloca memória para a nova string
        char* newSentence = malloc(newSentenceLength);
        if (newSentence == NULL)
        {
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

// size_t	ft_strlcpy_open(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	len;
// 	size_t	control;
// 	size_t	i;

// 	len = ft_strlen(src);
// 	i = 0;
// 	if (dstsize)
// 	{
// 		if (dstsize > len)
// 			control = len;
// 		else
// 			control = dstsize - 1;
// 		while (i < control)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 	}
// 	return (len);
// }
