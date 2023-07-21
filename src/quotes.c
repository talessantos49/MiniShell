/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:46:35 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:49:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_quote(t_block *current, char line)
{
	if (line == '\'')
		current->quote = '\'';
	else if (line == '\"')
		current->quote = '\"';
	else
		return (0);
	return (1);
}
