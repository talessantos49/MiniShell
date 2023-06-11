# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:52:33 by macarval          #+#    #+#              #
#    Updated: 2023/06/10 17:13:19 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
NAME_BONUS		= minishell_bonus

FILE_PATH		= ./src
FILE_PATH_BONUS	= ./src_bonus
OBJS_PATH		= ./obj
LIBFT_PATH		= ./libs/libft

HEADERS			= headers/minishell.h
HEADERS_BONUS	= headers/minishell_bonus.h

LIBFT			= $(LIBFT_PATH)/libft.a

FILES			= main.c \
				minishell.c \
				pipe_list.c \
				execution.c \
				split_commands.c \
				built_in.c \
				echo.c \
				exit.c \
				env.c \
				export.c \
				pwd.c \
				unset.c \
				utils.c \
				cd.c \
				heredoc.c \
				signals.c \
				clear.c \
				args.c \
				flags.c \
				perror_free_exit.c
FILES_BONUS		= minishell_bonus.c

IFLAGS			= -I./libs/libft
LFLAGS			= -L./libs/libft -lreadline -lft
CFLAGS			= -Wall -Wextra -Werror -g

CC				= gcc
RM				= rm -rf

OBJS			= $(addprefix $(OBJS_PATH)/, $(FILES:.c=.o))
OBJS_BONUS		= $(addprefix $(OBJS_PATH)/, $(FILES_BONUS:.c=.o))

all:			$(NAME)
$(NAME):		$(LIBFT) $(OBJS_PATH) $(OBJS)
				@$(CC) $(OBJS) -o $(NAME) $(LFLAGS)
				@echo "Minishell created!!"

bonus:			$(NAME_BONUS)
$(NAME_BONUS):	$(LIBFT) $(OBJS_PATH) $(OBJS_BONUS)
				@$(CC) $(OBJS_BONUS) -o $(NAME_BONUS) $(LFLAGS)
				@echo "Minishell bonus created!!"

$(OBJS_PATH):
				@mkdir -p $(OBJS_PATH)


$(OBJS_PATH)/%.o: $(FILE_PATH)/%.c $(HEADERS)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJS_PATH)/%.o: $(FILE_PATH_BONUS)/%.c $(HEADERS_BONUS)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
			
$(LIBFT):
				@make -C $(LIBFT_PATH)
					
clean:
				@$(RM) $(OBJS) $(OBJS_BONUS)
				@echo "clean Done!"

fclean:			clean
				@make -C $(LIBFT_PATH) fclean
				@$(RM) $(NAME) $(NAME_BONUS) $(OBJS_PATH)
				@echo "fclean Done!"

re:				fclean all

.PHONY: 		all bonus clean fclean re