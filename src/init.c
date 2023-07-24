/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:18:38 by root              #+#    #+#             */
/*   Updated: 2023/07/24 03:14:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_shell(t_shell **shell)
{
	(*shell)->env_mtx = NULL;
	(*shell)->paths_mtx = NULL;
	(*shell)->line = NULL;
	(*shell)->heredoc_name = NULL;
	(*shell)->actual_path = NULL;
	(*shell)->exit_code = 0;
	(*shell)->count = 0;
	(*shell)->env_n = 0;
	(*shell)->paths_n = 0;
	(*shell)->pipelist_n = 0;
	(*shell)->status = 0;
	(*shell)->pipelist = NULL;
	(*shell)->env = NULL;
}
