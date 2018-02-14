#  **************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/01 00:00:00 by jcarra            #+#    #+#              #
#    Updated: 2017/12/12 15:20:21 by jcarra           ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #

NAME		=	nm_otool
NAME_NM		=	ft_nm
NAME_OTOOL	=	ft_otool

SRC_TOOLS   =   ft_tools.c

SRC_NM		=	ft_print.c \
				ft_header64.c \
				ft_header32.c \
                ft_nm.c

SRC_OTOOL	=	ft_otool.c

LIB		=	libft.a

DIRSRC_TOOLS	=	sources/tools/
DIRSRC_NM	=	sources/ft_nm/
DIRSRC_OTOOL	=	sources/ft_otool/
DIRINC		=	include/
DIRLIB		=	library/

SRCS_TOOLS	=	$(SRC_TOOLS:%=$(DIRSRC_TOOLS)%)
SRCS_NM		=	$(SRC_NM:%=$(DIRSRC_NM)%)
SRCS_OTOOL	=	$(SRC_OTOOL:%=$(DIRSRC_OTOOL)%)
LIBS		=	$(LIB:%=$(DIRLIB)%)

OBJS_TOOLS	=	$(SRCS_TOOLS:.c=.o)
OBJS_NM		=	$(SRCS_NM:.c=.o)
OBJS_OTOOL	=	$(SRCS_OTOOL:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC) -g3
LFLAGS		=

CC		=	gcc
RM		=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:	$(NAME_NM) $(NAME_OTOOL)
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[34mAll\033[0m] ->\033[32m\tReady\n\033[0m'

$(NAME_NM)	:	.libft .hide_nm
			@$(CC) $(CFLAGS) -o $(NAME_NM) $(OBJS_TOOLS) $(OBJS_NM) $(LIBS) $(LFLAGS)

$(NAME_OTOOL)	:	.libft .hide_otool
			@$(CC) $(CFLAGS) -o $(NAME_OTOOL) $(OBJS_TOOLS) $(OBJS_OTOOL) $(LIBS) $(LFLAGS)

%.o		:	%.c
			@$(CC) -o $@ -c $< $(CFLAGS)
			@$(ECHO) '\-\> \033[36m$@\033[0m\n'

.hide_nm	:	$(OBJS_TOOLS) $(OBJS_NM)
			@touch .hide_nm
			@chmod 755 .hide_nm
			@$(ECHO) '\033[32m>\033[0m $(NAME_NM)    : [\033[33mft_nm\033[0m]    ->\033[32m	Ready\n\033[0m'

.hide_otool	:	$(OBJS_TOOLS) $(OBJS_OTOOL)
			@touch .hide_otool
			@chmod 755 .hide_otool
			@$(ECHO) '\033[32m>\033[0m $(NAME_OTOOL) : [\033[33mft_otool\033[0m] ->\033[32m	Ready\n\033[0m'

.libft		:
			@touch .libft
			@chmod 755 .libft
			@$(MAKE) $(DIRLIB)

clean		:
			@$(MAKE) $(DIRLIB) clean
			@if [ -e .hide_nm ]; \
			then \
				$(RM) $(OBJS_NM) .hide_nm .libft; \
				$(ECHO) '\r\033[38;5;202m✗ $(NAME_NM)\033[0m\033[0m\n'; \
			fi;
			@if [ -e .hide_otool ]; \
			then \
				$(RM) $(OBJS_OTOOL) .hide_otool .libft; \
				$(ECHO) '\r\033[38;5;202m✗ $(NAME_OTOOL)\033[0m\033[0m\n'; \
			fi;
			@if [ -e $(OBJS_TOOLS) ]; \
			then \
				$(RM) $(OBJS_TOOLS) .libft; \
			fi;

fclean		:	clean
			@$(MAKE) $(DIRLIB) fclean
			@if [ -e $(NAME_NM) ]; \
			then \
				$(RM) $(NAME_NM); \
				$(ECHO) "\r\033[38;5;196m✗ $(NAME_NM)\033[0m\033[0m\n"; \
			fi;
			@if [ -e $(NAME_OTOOL) ]; \
			then \
				$(RM) $(NAME_OTOOL); \
				$(ECHO) "\r\033[38;5;196m✗ $(NAME_OTOOL)\033[0m\033[0m\n"; \
			fi;

re		:	fclean all

.PHONY		:	all clean fclean re

