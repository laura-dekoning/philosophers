# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lade-kon <lade-kon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/11 15:53:12 by lade-kon      #+#    #+#                  #
#    Updated: 2024/11/12 09:33:31 by lade-kon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME			:=	philo

CC				:=	cc
#CFLAGS are the compiler flags: show all warnings and include debug info
CFLAGS			:=	-Wall -Werror -Wextra -g -fsanitize=address
TFLAGS			:=	-pthread

INCLS_PHILO		:=	incl
INCLUDES		:=	-I $(INCLS_PHILO)

SRC_DIR			:=	src

SRC_FILES		:=	main.c \
					parser.c \
					init.c \
					dinner.c \
					utils.c \
					time.c \
					print.c \


SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR			:=	obj
OBJ_FILES		:=	$(SRC_FILES:.c=.o)
OBJ				:=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILES))


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) 
	$(CC) $(CFLAGS) $(TFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDES) -c $< -o $@


norminette:
	@echo "${CYAN}🧐 Checking the Norm...${RESET}"
	@norminette -R CheckForbiddenSourceHeader
	@echo "${GREEN} Norm-i-netting complete. Files are NORM PROOF!${RESET}" 

update:
	@git submodule update --init --recursive --remote

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

## Colours ##
RESET	:= \033[0m
RED		:= \033[1;91m
GREEN	:= \033[1;92m
YELLOW	:= \033[1;93m
BLUE	:= \033[1;94m
PURPLE	:= \033[1;95m
CYAN	:= \033[1;96m
WHITE	:= \033[1;97m
BLACK	:= \033[1;90m