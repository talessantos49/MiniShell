/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:45:57 by root              #+#    #+#             */
/*   Updated: 2023/08/15 20:21:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_quote
{
	QUOTE_OPEN = 1,
	QUOTE_CLOSE
};

enum	e_return
{
	SUCCES,
	EXCEPTION
};

enum	e_set
{
	NEW_BLOCK,
	COMMAND,
	INFILE,
	OUTFILE_NEW,
	OUTFILE_APPEND,
	TEST_HEREDOC
};

#endif