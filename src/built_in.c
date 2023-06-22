/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/06/21 19:47:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int builtin_setup(t_shell **shell, char **args)
{
	(*shell)->command = args[0];
	(*shell)->flag = args[1];
	if (args[2])
		(*shell)->content = args[2];
	else
		(*shell)->content = args[1];
	return (0);	
}

void *is_built_in(char *command)
{
	if (!strcmp_mod(command, "cd"))
		return (c_cd);
	if (!strcmp_mod(command, "clear"))
		return (c_clear);
	if (!strcmp_mod(command, "echo"))
		return (c_echo);
	if (!strcmp_mod(command, "env"))
		return (c_env);
	if (!strcmp_mod(command, "exit"))
		return (c_exit);
	if (!strcmp_mod(command, "export"))
		return (c_export);
	if (!strcmp_mod(command, "pwd"))
		return (c_pwd);
	if (!strcmp_mod(command, "unset"))
		return (c_unset);
	return (NULL);
}