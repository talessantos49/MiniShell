/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/06/22 09:12:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Passar norminette

void	c_echo(t_shell **shell)
{
	t_env	*node;
	char	*temp_line;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp_line = (*shell)->line;
	while (temp_line[i])
	{
		if (temp_line[i] == '$')
			k++;
		i++;
	}
	printf("%d, %s\n", k, temp_line);
	printf("(*shell)->content: %s\n", (*shell)->content);
	printf("(*shell)->content[0]: %c\n", (*shell)->content[0]);
	//Isso ta errado, precisamos mudar pra quando tiver mais de uma variavel com entrada $var
	if ((*shell)->content && (*shell)->content[0] == '$' && (*shell)->content[1] != '?')
	{
		node = find_arg(shell, ++(*shell)->content);
		if (node)
			printf("%s", node->msg);
	}
	else if ((*shell)->content[0] == '$' && (*shell)->content[1] == '?')
		printf("%d", (*shell)->exit_code);
	else
		printf("%s", (*shell)->content);
	if (!(*shell)->flag || strcmp_mod((*shell)->flag, "-n"))
		printf("\n");
}
