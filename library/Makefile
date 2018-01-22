#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/08/29 21:32:58 by wescande          #+#    #+#             *#
#*   Updated: 2016/12/24 02:14:21 by wescande         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME		=	libft.a

CC		=	gcc
FLAGS		=	-Wall -Wextra -Werror

LEN_NAME	=	`printf "%s" $(NAME) | wc -c`
DELTA		=	$$(echo "$$(tput cols)-31-$(LEN_NAME)"|bc)

SRC_DIR		=	sources/
INC_DIR		=	include/
OBJ_DIR		=	objs/

SRC_BASE	=	ft_strcmp.c \
			ft_strncmp.c \
			ft_strcmp_case.c \
			ft_strchr.c \
			ft_strlchr.c \
			ft_strrchr.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_atoi.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_memset.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isprint.c \
			ft_isascii.c \
			ft_isoct.c \
			ft_ishex.c \
			ft_esc_hex.c \
			ft_eval_esc.c \
			ft_evaluator.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strclr.c \
			ft_strdel.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_putendl.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_revnbr.c \
			ft_revstr.c \
			ft_tablen.c \
			btree_create_node.c \
			btree_insert_data.c \
			btree_add_node.c \
			btree_apply_infix.c \
			btree_apply_prefix.c \
			btree_apply_suffix.c \
			ft_create_elem.c \
			ft_list_push_back.c \
			ft_list_push_front.c \
			ft_list_size.c \
			ft_list_last.c \
			ft_list_push_params.c \
			ft_list_clear.c \
			ft_list_at.c \
			ft_list_reverse.c \
			ft_list_foreach.c \
			ft_list_del.c \
			ft_list_sort.c \
			get_next_line.c


SRCS		=	$(SRC_BASE:%=$(SRC_DIR)%)
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB		=	$(words $(SRC_BASE))
INDEX		=	0
SHELL		:=	/bin/bash

all :
	@$(MAKE) -j $(NAME)

$(NAME) :		$(OBJ_DIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\r\033[38;5;117m✓ MAKE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean :
	@if [ -e $(OBJ_DIR) ]; \
	then \
		rm -rf $(OBJ_DIR); \
		printf "\r\033[38;5;202m✗ clean $(NAME).\033[0m\033[K\n"; \
	fi;

fclean :		clean
	@if [ -e $(NAME) ]; \
	then \
		rm -rf $(NAME); \
		printf "\r\033[38;5;196m✗ fclean $(NAME).\033[0m\033[K\n"; \
	fi;

re :			fclean all

.PHONY :		fclean clean re

-include $(OBJS:.o=.d)

