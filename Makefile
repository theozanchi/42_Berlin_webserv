# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 11:40:43 by tzanchi           #+#    #+#              #
#    Updated: 2024/03/11 19:23:58 by tzanchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler targets and libraries
CC			=	c++
# CFLAGS		=	-Wall -Wextra -Werror -std=c++98
CFLAGS		+=	-I$(patsubst %/,%,$(patsubst ./%,%,$(SRCS_DIR)))
NAME		=	webserv

# Directories
SRCS_DIR	=	./src/
INCS_DIR	=	./inc/
OBJ_DIR		=	./obj/

# Colours, symbols and utils
GREEN		=	\033[1;32m
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
NC			=	\033[0m
BOLD		=	\033[1m
TICK		=	✓

SRC			=	class/ALocation.cpp \
				class/CGI.cpp \
				class/Configuration.cpp \
				class/Server.cpp \
				class/StdLocation.cpp \
				class/Upload.cpp \
				\
				main.cpp \
				Parser_ServerBlock.cpp \
				Parser.cpp

SRCS		=	$(addprefix ${SRCS_DIR}, ${SRC})
SRC_NR		=	$(words ${SRCS})

OBJS		=	$(patsubst ${SRCS_DIR}%, ${OBJ_DIR}/%, $(SRCS:.cpp=.o))

all:			project_logo ${NAME}

${NAME}:		entry_message ${OBJS}
				@if [ -e ${NAME} ] && [ "$(shell find ${OBJ_DIR} -newer ${NAME} 2>/dev/null)" = "" ]; then \
					echo "Nothing to do\n"; \
				else \
					${CC} ${CFLAGS} ${OBJS} -o ${NAME}; \
					echo "${YELLOW}\nCompilation complete, ${NAME} executable at the root of the directory${NC}\n";\
				fi

$(OBJ_DIR)/%.o:	$(SRCS_DIR)%.cpp
				@mkdir -p $(dir $@)
				@printf "Compiling $(notdir $<)"; \
				${CC} ${CFLAGS} -I${INCS_DIR} -c $< -o $@; \
				printf "${GREEN}"; \
				printf " ${TICK}\n"; \
				printf "${NC}"; 

clean:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "Repo already clean"; \
				else \
					echo "Removing all .o files"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean:			clean
				@echo "Removing executable from root"
				@rm -f ${NAME}

re:				fclean
				@echo "\n${GREEN}COMPILING WITHOUT DEBUG FLAG${NC}\n"
				@make --no-print-directory all


go:				all
				@./${NAME}

vgo:			all
				valgrind -s --leak-check=full ./${NAME}

debug:			fclean
				$(eval CFLAGS += -g)
				@echo "\n${GREEN}COMPILING WITH DEBUG FLAG${NC}\n"
				@make --no-print-directory all

project_logo:
				@echo "      _________ "
				@echo "     / ======= \ "
				@echo "    / __________\ "
				@echo "   | ___________ |"
				@echo "   | | $(RED)-$(NC)       | |"
				@echo "   | |         | |"
				@echo "   | |_________| |________________________"
				@echo "   \=____________/     $(BOLD)Selina Pradel$(NC)      )"
				@echo "   / \"\"\"\"\"\"\"\"\"\"\" \     $(BOLD)Lola Le$(NC)           /"
				@echo "  / $(CYAN):::::::::::::$(NC) \    $(BOLD)Théo Zanchi$(NC)      /"
				@echo " (_________________)                =D-'\n"

entry_message:
				@echo "${CYAN}COMPILING $$(echo ${NAME} | tr '[:lower:]' '[:upper:]')\n${NC}${BOLD}Compiling necessary .o files out of $(SRC_NR) files:${NC}"

.PHONY:			all clean fclean re go vgo debug project_logo entry_message