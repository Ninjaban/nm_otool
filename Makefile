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

NAME_NM		=	ft_nm
NAME_OTOOL	=	ft_otool


SRC_NM		=
SRC_OTOOL	=

LIB		=	libft.a

DIRSRC		=	sources/
DIRINC		=	include/
DIRLIB		=	library/

SRCS_NM		=	$(SRC_NM:%=$(DIRSRC)%)
SRCS_OTOOL	=	$(SRC_OTOOL:%=$(DIRSRC)%)
LIBS		=	$(LIB:%=$(DIRLIB)%)

OBJS_NM		=	$(SRCS_NM:.c=.o)
OBJS_OTOOL	=	$(SRCS_OTOOL:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC)
LFLAGS		=	-lncurses

CC		=	gcc
RM		=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:	$(NAME_NM) $(NAME_OTOOL)
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[34mAll\033[0m] ->\033[32m\tReady\n\033[0m'

$(NAME_NM)	:	.libft .hide_nm
			@$(CC) $(CFLAGS) -o $(NAME_NM) $(OBJS_NM) $(LIBS) $(LFLAGS)

$(NAME_OTOOL)	:	.libft .hide_otool
			@$(CC) $(CFLAGS) -o $(NAME_OTOOL) $(OBJS_OTOOL) $(LIBS) $(LFLAGS)

%.o		:	%.c
			@$(CC) -o $@ -c $< $(CFLAGS)
			@$(ECHO) '\-\> \033[36m$@\033[0m\n'

.hide_nm	:	$(OBJS)
			@touch .hide_nm
			@chmod 755 .hide_nm
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mft_nm\033[0m]    ->\033[32m	Ready\n\033[0m'

.hide_otool	:	$(OBJS)
			@touch .hide_otool
			@chmod 755 .hide_otool
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mft_otool\033[0m] ->\033[32m	Ready\n\033[0m'

.libft		:
			@touch .libft
			@chmod 755 .libft
			@$(MAKE) $(DIRLIB)

clean		:
			@$(MAKE) $(DIRLIB) fclean
			@$(RM) $(OBJS) .hide_nm .hide_otool .libft
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mDirectory cleaned\n\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mRemove executable\n\033[0m'

re		:	fclean all

.PHONY		:	all clean fclean re

