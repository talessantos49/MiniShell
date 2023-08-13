/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/07/19 16:38:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef   MINISHELL_H
# define  MINISHELL_H

# include	<fcntl.h>
# include 	<readline/history.h>
# include 	<readline/readline.h>
# include 	<stdarg.h>
# include 	<string.h>
# include 	<sys/types.h>
# include 	<sys/uio.h>
# include 	<sys/wait.h>
# include 	<signal.h>
# include 	<stdio.h>
# include 	<stdlib.h>
# include 	<unistd.h>

# include "../lib/libft/libft.h"
# include "constants.h"
# include "enums.h"
# include "structs.h"
# include "prototypes.h"

extern int			g_signal;

#endif