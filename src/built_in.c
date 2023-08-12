/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/07/19 16:24:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	*is_built_in(char *command)
{
	if (!strcmp_mod(command, NAME_CD))
		return (c_cd);
	if (!strcmp_mod(command, NAME_ECHO))
		return (c_echo);
	if (!strcmp_mod(command, NAME_ENV))
		return (c_env);
	if (!strcmp_mod(command, NAME_EXIT))
		return (c_exit);
	if (!strcmp_mod(command, NAME_EXPORT))
		return (c_export);
	if (!strcmp_mod(command, NAME_PWD))
		return (c_pwd);
	if (!strcmp_mod(command, NAME_UNSET))
		return (c_unset);
	return (NULL);
}
