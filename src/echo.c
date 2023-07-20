/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/07/20 12:55:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	print_args_echo(t_cmd *list)
char	*print_args_echo(t_cmd *list)
{
	t_cmd	*temp;
	char	*cmd;
	char	*flag;
	char	*temp_str;

	flag = "-n";
	cmd = "echo";
	temp = list;
	// temp_str = NULL;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->arg, cmd))
			temp = temp->next;
		else if (!strcmp_mod(temp->arg, flag))
			temp = temp->next;
		else if (temp->next != NULL)
		{
			temp_str = ft_strjoin(temp_str, temp->arg);
			temp_str = ft_strjoin(temp_str, " ");
			// printf("%s ", temp->arg);
			temp = temp->next;
		}
		else
		{
			temp_str = ft_strjoin(temp_str, temp->arg);
			// printf("%s", temp->arg);
			temp = temp->next;
		}
	}
	temp_str = ft_strip(temp_str, '\'');
	temp_str = ft_strip(temp_str, '\"');
	// printf("%s", temp_str);
	return (temp_str);
}

char	*flag_echo(t_shell **shell)
{
	char	*temp_line;
	char	*flag;
	char	*test;

	test = "-n";
	if ((*shell)->pipelist->commands->next == NULL)
	{
		flag = ft_strdup("");
		return (NULL);
	}
	temp_line = (*shell)->pipelist->commands->next->arg;
	if ((*shell)->line == NULL)
		return (NULL);
	if (temp_line[0] == test[0] && temp_line[1] == test[1])
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

char	*search_and_destroy(t_shell **shell, char *printable)
{
	int		i;
	char	*temp;
	int		k;

	i = 0;
	k = 0;
	temp = ft_calloc(sizeof (char*), ft_strlen(printable));
	while (printable[i])
	{
		if (((*shell)->pipelist->quote_position[k] - 6)== i)
		{
			temp[i] = printable[i];
			if (temp[i] == '#')
				temp[i] = '$';
			k++;
		}
		else
			temp[i] = printable[i];
		i++;
	}
	return (temp);
}

void	c_echo(t_shell **shell)
{
	char	*flag;
	char	*printable;

	if ((*shell)->line == NULL)
		return ;
	flag = flag_echo(shell);
	printable = print_args_echo((*shell)->pipelist->commands);
	printable = search_and_destroy(shell, printable);
	printf("%s", printable);
	if (flag == NULL || (*shell)->pipelist->commands->next == NULL
		|| strcmp_mod(flag, "-n"))
		printf("\n");
	(*shell)->exit_code = 0;
	free (flag);


	// t_cmd quotes tem o quote aberto e usar o quote_clean;
}
