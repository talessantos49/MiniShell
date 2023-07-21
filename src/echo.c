/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/07/21 18:30:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	print_args_echo(t_cmd *list)
char	*print_args_echo(t_cmd *list, int flag_int)
{
	t_cmd	*temp;
	char	*cmd;
	char	*flag;
	char	*temp_str;

	flag = "-n";
	cmd = "echo";
	temp = list;
	temp_str = ft_strdup("");
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->arg, cmd))
			temp = temp->next;
		else if (!strcmp_mod(temp->arg, flag) && flag_int == 1)
			temp = temp->next;
		else if (temp->next != NULL)
		{
			flag_int = 0;
			// if (temp->arg[0] == '\'' || temp->arg[0] == '\"')
			// {
				// temp->arg = ft_strip(temp->arg, '\'');
				// temp->arg = ft_strip(temp->arg, '\"');
			// 	temp_str = ft_strjoin(temp_str, temp->arg);
			// }
			// else
			// {
				temp_str = ft_strjoin(temp_str, temp->arg);
				temp_str = ft_strjoin(temp_str, " ");
			// }
			temp = temp->next;
		}
		else
		{
		// 	temp->arg = ft_strip(temp->arg, '\'');
		// 	temp->arg = ft_strip(temp->arg, '\"');
			temp_str = ft_strjoin(temp_str, temp->arg);
			// temp_str = ft_strtrim(temp_str, "\"");
			// temp_str = ft_strtrim(temp_str, "\'");
			// printf("%s", temp->arg);
			temp = temp->next;
		}
	}
	// temp_str = ft_strip(temp_str, '\'');
	// temp_str = ft_strip(temp_str, '\"');
	// printf("%s", temp_str);
	return (temp_str);
}

// char	*flag_echo(t_shell **shell)
// {
// 	char	*temp_line;
// 	char	*flag;
// 	char	*test;

// 	test = "-n";
// 	if ((*shell)->pipelist->commands->next == NULL)
// 	{
// 		flag = ft_strdup("");
// 		return (NULL);
// 	}
// 	temp_line = (*shell)->pipelist->commands->next->arg;
// 	if ((*shell)->line == NULL)
// 		return (NULL);
// 	if (temp_line[0] == test[0] && temp_line[1] == test[1])
// 	{
// 		flag = ft_strdup("-n");
// 		if (temp_line[0] == test[0] && temp_line[1] == test[1])
// 			(*shell)->line = " ";
// 		else
// 			(*shell)->line = temp_line;
// 	}
// 	else
// 		flag = ft_strdup("");
// 	return (flag);
// }

int	flag_echo(t_shell **shell)
{
	char	*temp_line;
	int		flag;
	// char	*test;

	if ((*shell)->pipelist->commands->next == NULL)
		return (0);
	temp_line = (*shell)->pipelist->commands->next->arg;
	if ((*shell)->line == NULL)
		return (0);
	if (temp_line[0] == '-' && temp_line[1] == 'n')
	{
		flag = 1;
		if (temp_line[0] == '-' && temp_line[1] == 'n')
			(*shell)->line = " ";
		else
			(*shell)->line = temp_line;
	}
	else
		flag = 0;
	return (flag);
}

void	c_echo(t_shell **shell)
{
	int		flag;
	char	*printable;

	if ((*shell)->line == NULL)
		return ;
	flag = flag_echo(shell);
	printable = print_args_echo((*shell)->pipelist->commands, flag);
	printf("%s", printable);
	if (flag == 0 || (*shell)->pipelist->commands->next == NULL)
		printf("\n");
	(*shell)->exit_code = 0;
	// free (flag);
	// if ((*shell)->line == NULL)
	// 	return ;
	// flag = flag_echo(shell);
	// printable = print_args_echo((*shell)->pipelist->commands);
	// printf("%s", printable);
	// if (flag == NULL || (*shell)->pipelist->commands->next == NULL
	// 	|| strcmp_mod(flag, "-n"))
	// 	printf("\n");
	// (*shell)->exit_code = 0;
	// free (flag);
}
