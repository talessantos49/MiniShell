# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:52:33 by macarval          #+#    #+#              #
#    Updated: 2023/07/15 22:31:40 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILE_PATH		= ./src
OBJS_PATH		= ./obj
LIBFT_PATH		= ./lib/libft

HEADERS			= inc/minishell.h

LIBFT			= $(LIBFT_PATH)/libft.a

FILES			= main.c \
				minishell.c \
				builtins.c \
				cd.c \
				echo.c \
				env.c \
				execution.c \
				execve_matrixes.c \
				exit.c \
				export.c \
				heredoc.c \
				perror_free_exit.c \
				pipe_list.c \
				pwd.c \
				quotes.c \
				signals.c \
				split_commands.c \
				unset.c \
				utils.c \
				validations_input.c \
				validations_input2.c

IFLAGS			= -I./lib/libft
LFLAGS			= -L./lib/libft -lreadline -lft
CFLAGS			= -Wall -Wextra -Werror -g

CC				= gcc
RM				= rm -rf

OBJS			= $(addprefix $(OBJS_PATH)/, $(FILES:.c=.o))

all:			$(NAME)
$(NAME):		$(LIBFT) $(OBJS_PATH) $(OBJS)
				@$(CC) $(OBJS) -o $(NAME) $(LFLAGS)
				@echo "Minishell created!!"

$(OBJS_PATH):
				@mkdir -p $(OBJS_PATH)


$(OBJS_PATH)/%.o: $(FILE_PATH)/%.c $(HEADERS)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
			
$(LIBFT):
				@make -C $(LIBFT_PATH)
					
clean:
				@$(RM) $(OBJS)
				@echo "clean Done!"

fclean:			clean
				@make -C $(LIBFT_PATH) fclean
				@$(RM) $(NAME) $(OBJS_PATH)
				@echo "fclean Done!"

re:				fclean all

.PHONY: 		all clean fclean re


#VALGRIND		= @valgrind --leak-check=full --show-leak-kinds=all \
#--track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes --verbose \
#--trace-children=yes --track-fds=yes \
#--log-file=valgrind-out.txt

VALGRIND 		= @valgrind --leak-check=full --show-leak-kinds=all \
--track-origins=yes --trace-children=yes --suppressions=readline.supp --log-file=valgrind-out.txt -s

valgrind:
	$(VALGRIND) ./minishell
