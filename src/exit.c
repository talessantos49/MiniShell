/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:15 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:01:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_number(char *str)
{
	str += (str[0] == CHAR_MINUS || str[0] == CHAR_PLUS);
	if (*str)
	{
		while (*str && ft_isdigit(*str))
			str++;
		if (!*str)
			return (TRUE);
	}
	return (FALSE);
}


void	c_exit(t_shell **shell)
{
	int8_t	exit_code;

	if ((*shell)->pipelist->args[1] \
	&& !is_number((*shell)->pipelist->args[1]))
	{
		perror((*shell)->pipelist->args[1]);
		(*shell)->exit_code = 2;
	}
	else if ((*shell)->pipelist->args[1])
		(*shell)->exit_code = ft_atoi((*shell)->pipelist->args[1]);
	exit_code = (*shell)->exit_code;
	free_shell(shell);
	exit(exit_code);
}
