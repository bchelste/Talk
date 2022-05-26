# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 21:59:34 by bchelste          #+#    #+#              #
#    Updated: 2021/09/18 22:36:44 by bchelste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= server

NAME2				= client

NAME_BONUS			= server_bonus

NAME_BONUS2			= client_bonus

CC 					= gcc

CFLAGS 				= -Wall -Werror -Wextra

OPTFLAGS			= -O2

RM 					= rm -f

SRCSDIR 			= minitalk

BONUSDIR 			= bonus

UTILSDIR 			= utils

INCDIR				= includes

SRCS				= $(SRCSDIR)/server.c

OBJS				= $(SRCS:.c=.o)

SRCS2				= $(SRCSDIR)/client.c

OBJS2				= $(SRCS2:%.c=%.o)

SRCS_BONUS			= $(BONUSDIR)/server_bonus.c
			
OBJS_BONUS			= $(SRCS_BONUS:%.c=%.o)

SRCS_BONUS2			= $(BONUSDIR)/client_bonus.c
			
OBJS_BONUS2			= $(SRCS_BONUS2:%.c=%.o)

SRCS_UTILS			= $(UTILSDIR)/utils.c
			
OBJS_UTILS			= $(SRCS_UTILS:%.c=%.o)

INC					= -I$(INCDIR)	

%.o:%.c
					$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@ $(INC)

.PHONY: all clean fclean re bonus

all:				
					$(MAKE) $(NAME) -j 4
					$(MAKE) $(NAME2) -j 4

bonus:
					$(MAKE) $(NAME_BONUS) -j 4
					$(MAKE) $(NAME_BONUS2) -j 4


$(NAME): 			$(OBJS) $(OBJS_UTILS)
					$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) $(OBJS_UTILS) -o $(NAME)

$(NAME2):			$(OBJS2) $(OBJS_UTILS)
					$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS2) $(OBJS_UTILS) -o $(NAME2)

$(NAME_BONUS):		$(OBJS_BONUS) $(OBJS_UTILS)
					$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS_BONUS) $(OBJS_UTILS) -o $(NAME_BONUS)

$(NAME_BONUS2):		$(OBJS_BONUS2) $(OBJS_UTILS)
					$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS_BONUS2) $(OBJS_UTILS) -o $(NAME_BONUS2)

clean:		
					$(RM) $(OBJS) $(OBJS2) $(OBJS_BONUS) $(OBJS_BONUS2) $(OBJS_UTILS)

fclean:				clean
					$(RM) $(NAME) $(NAME2) $(NAME_BONUS) $(NAME_BONUS2)

re:					fclean all bonus