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