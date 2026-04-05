# ================== CONFIGURATION ================== #
NAME      := PmergeMe
CC        := c++
CFLAGS    := -Wall -Wextra -Werror -g -std=c++98
OPTIONS   := -I includes

SRC_FILES := main.cpp PmergeMe.cpp
OBJ_DIR   := obj
SRC   := $(SRC_FILES)
OBJS  := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

# ================== COULEURS ================== #
GREEN  = \033[32m
BLUE   = \033[34m
RESET  = \033[0m
RED    = \033[31m

# ================== RÈGLES ================== #
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OPTIONS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ Compilation réussie!$(RESET)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "$(RED)✓ Objets supprimés.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)✓ Exécutable supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
