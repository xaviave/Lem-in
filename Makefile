# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/20 15:30:33 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2018/06/07 15:13:46 by xamartin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY = all, clean, fclean, re


#COMPILATION

CC = gcc
NAME = lem-in
INC = -I includes/
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/


#PATH

SCRS_PATH = ./srcs/
OBJS_PATH = ./srcs/
FILES = main_lemin.c\
		parse_lemin.c\
		parse_room.c\
		parse_room2.c\
		parse_link.c\
		tab_init.c\
		find_path.c\
		find_path2.c\
		find_path3.c\
		find_init.c\
		aff_path.c\
		print_path.c\

SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(addprefix $(OBJS_PATH), $(FILES:.c=.o))


#RULES

all: $(NAME)


$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) -g $(CFLAGS) $(INC) -o $@ $(OBJS) -L $(LIBFT) -lft

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<


clean:
	@make -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all
	@make -C $(LIBFT) re
