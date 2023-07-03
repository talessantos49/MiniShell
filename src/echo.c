/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/07/03 13:29:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Passar norminette

// void	c_echo(t_shell **shell)
// {
// 	t_env	*node;
// 	char	*temp_line;
// 	int		i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	temp_line = (*shell)->line;
// 	while (temp_line[i])
// 	{
// 		if (temp_line[i] == '$')
// 			k++;
// 		i++;
// 	}
// 	printf("%d, %s\n", k, temp_line);
// 	printf("(*shell)->content: %s\n", (*shell)->content);
// 	printf("(*shell)->content[0]: %c\n", (*shell)->content[0]);
// 	//Isso ta errado, precisamos mudar pra quando tiver mais de uma variavel com entrada $var
// 	if ((*shell)->content && (*shell)->content[0] == '$' && (*shell)->content[1] != '?')
// 	{
// 		node = find_arg(shell, ++(*shell)->content);
// 		if (node)
// 			printf("%s", node->msg);
// 	}
// 	else if ((*shell)->content[0] == '$' && (*shell)->content[1] == '?')
// 		printf("%d", (*shell)->exit_code);
// 	else
// 		printf("%s", (*shell)->content);
// 	if (!(*shell)->flag || strcmp_mod((*shell)->flag, "-n"))
// 		printf("\n");
// }

char	*flag_echo(t_shell **shell)
{
	char	*temp_line;
	char	*flag;
	char	*test;

	test= "-n";
	temp_line = (*shell)->line;
	if ((*shell)->line == NULL)
		return (NULL);
	if ((*shell)->flag != NULL && (*shell)->flag[0] == test[0] && (*shell)->flag[1] == test[1])
	{
		flag = ft_strdup("-n");
		if (temp_line[0] == test[0] && temp_line[1] == test[1])
			(*shell)->line = "";
		else
			(*shell)->line = temp_line;
	}
	else
		flag = ft_strdup("");
	return (flag);
}

void	c_echo(t_shell **shell)
{
	t_env	*temp_node;
	char	*temp_line;
	char	*flag;
	int		i;
	int		len_var;

	i = 0;
	len_var = 0;
	if ((*shell)->line == NULL)
		return ;
	flag = flag_echo(shell);
	temp_line = (*shell)->line;
	temp_node = (t_env *)ff_calloc(1, sizeof (t_env));
	if ((find(temp_line, '$')) == 1)
	{
		while (temp_line[i])
		{
			if (temp_line[i] == '$' && temp_line[i + 1] == '?')
			{
				i++;
				printf("%d", (*shell)->exit_code);
			}
			else if (temp_line[i] == '$')
			{
				temp_line += i;
				temp_node = find_arg(shell, ++temp_line);
				printf("%s", temp_node->msg);
				len_var = ft_strlen(temp_node->msg);
			}
			else
				printf("%c", temp_line[i]);
			i++;
			i = i + len_var;
		}
	}
	else
		printf("%s", temp_line);
	if (strcmp_mod(flag, "-n"))
		printf("\n");
	(*shell)->exit_code = 0;
}
