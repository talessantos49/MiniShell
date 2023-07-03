/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/03/28 00:46:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
