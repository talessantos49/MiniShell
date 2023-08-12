/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/07/17 11:23:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**flag_scan(t_block *current)
{
	char	**args;
	int		has_flag_valid;	

	args = &current->args[1];
	has_flag_valid = 0;
	while(args && *args && \
	(**args == *STR_VOID || !strcmp_mod(*args, STR_FLAG_ECHO)))
	{
		has_flag_valid += (!strcmp_mod(*args, STR_FLAG_ECHO));
		args++;
	}
	if (has_flag_valid)
		return (args);
	else
		return (NULL);
}	

void	c_echo(t_shell **shell)
{
	char	**args;
	char	**flag;

	flag = flag_scan((*shell)->pipelist);
	if (flag)
		args = flag;
	else
		args = &(*shell)->pipelist->args[1];
	while (args && *args)
	{
		printf("%s", *args++);
		if (args && *args && **args)
			printf(" ");
	}
	if (!flag)
		printf("\n");
}
