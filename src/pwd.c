/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:32:46 by root              #+#    #+#             */
/*   Updated: 2023/07/22 13:39:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	c_pwd(t_shell **shell)
void	c_pwd(void)
{
	char	buf[256];

	// shell = (shell);
	// if (!is_flag_null(shell, ""))
	// 	exit(2);
	printf("%s\n", getcwd(buf, 256));
}
