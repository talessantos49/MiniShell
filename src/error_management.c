/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 02:15:27 by root              #+#    #+#             */
/*   Updated: 2023/07/24 02:15:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	perror_free(char *type, char *name)
{
	int	name_len;
	int	type_len;

	name_len = ft_strlen(name);
	type_len = ft_strlen(type);
	write(2, name, name_len);
	write(2, type, type_len);
	write(2, "\n", 1);
}

void	error(char *msg, t_shell **shell, int free_type, int exit_code)
{
	ft_putstr_fd(msg, 2);
	if (free_type)
		free_shell(shell);
	if (exit_code)
	{
		free_shell(shell);
		exit(exit_code);
	}
}
