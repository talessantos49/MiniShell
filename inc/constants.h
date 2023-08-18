/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:46:05 by root              #+#    #+#             */
/*   Updated: 2023/08/18 10:44:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef   CONSTANTS_H
# define  CONSTANTS_H

# define  BUF	 		256

# define  CHAR_EQUAL	'='
# define  CHAR_MINUS	'-'
# define  CHAR_Q_DOUBLE '\"'
# define  CHAR_Q_SINGLE	'\''
# define  CHAR_TILDE	'~'
# define  CHAR_VAR 		'$'
# define  CHAR_QUESTION '?'

# define  CHMOD	 		0644

# define  COLOR_BHCYAN	"\001\e[1;96m\002"
# define  COLOR_BHRED	"\001\e[1;91m\002"
# define  COLOR_RESET  	"\001\e[0m\002"

# define  ERROR_ARG     "MiniShell: too many arguments\n"
# define  ERROR_EXIT    "numeric argument required\n"
# define  ERROR_EXIT1   "too many arguments\n"

# define  ERROR_CD1     "MiniShell: cd: too many arguments\n"
# define  ERROR_CD2     "MiniShell: cd: OLDPWD not set\n"
# define  ERROR_CD3     "MiniShell: cd: %s: No such file or directory\n"
# define  ERROR_CMD     "%s: command not found\n"
# define  ERROR_EXPORT  "MiniShell: export: `%s': not a valid identifier\n"
# define  ERROR_FD_DIR  "MiniShell: %s: No such file or directory\n"
# define  ERROR_IO_CHAR "MiniShell: syntax error near unexpected token `%s%c'\n"
# define  ERROR_IS_DIR  "MiniShell: %s: Is a directory\n"
# define  ERROR_OPTION  "%s: invalid option or argument\n"

# define  KEY_HOME		"HOME"
# define  KEY_PWD		"PWD"
# define  KEY_OLDPWD	"OLDPWD"

# define  NAME_CD		"cd"
# define  NAME_ECHO		"echo"
# define  NAME_EXIT		"exit"
# define  NAME_ENV		"env"
# define  NAME_EXIT		"exit"
# define  NAME_EXPORT	"export"
# define  NAME_PWD		"pwd"
# define  NAME_UNSET	"unset"

# define  STR_FLAG_ECHO "-n"
# define  STR_HEREDOC	".tmp"
# define  STR_NEWLINE 	"newline"
# define  STR_QUOTES 	"\'\""
# define  STR_SLASH 	"/"
# define  STR_SPACES 	" \t\r\f\v"
# define  STR_SPECIALS 	"<>|"
# define  STR_VOID 		""

#endif