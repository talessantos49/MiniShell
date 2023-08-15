/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by root          #+#    #+#             */
/*   Updated: 2023/07/21 18:30:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*print_args_echo(t_cmd *list, int flag_int, char *cmd, char *flag)
{
	t_cmd	*temp;
	char	*temp_str;

	temp = list;
	temp_str = "";
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->arg, cmd))
			temp = temp->next;
		else if (!strcmp_mod(temp->arg, flag) && flag_int == 1)
			temp = temp->next;
		else if (temp->next != NULL)
		{
			flag_int = 0;
			temp_str = ft_strjoin(temp_str, temp->arg);
			temp_str = ft_strjoin(temp_str, " ");
			temp = temp->next;
		}
		else
		{
			temp_str = ft_strjoin(temp_str, temp->arg);
			temp = temp->next;
		}
	}
	return (temp_str);
}

int	flag_echo(t_shell **shell)
{
	char	*temp_line;
	int		flag;

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
	char	*temp_line;

	temp_line = "";
	if ((*shell)->line == NULL)
		return ;
	flag = flag_echo(shell);
	// printable = ft_strdup(print_args_echo(
	// 			(*shell)->pipelist->commands, flag, "echo", "-n"));
	printable = print_args_echo((*shell)->pipelist->commands,
			flag, "echo", "-n");
	printf("%s", printable);
	if (flag == 0 || (*shell)->pipelist->commands->next == NULL)
		printf("\n");
	if (printable != temp_line)
		free(printable);
	(*shell)->exit_code = 0;
}
