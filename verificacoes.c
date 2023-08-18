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
