
# Include directories
INCLUDES = -Iincludes

# Compiler and flags
CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror $(INCLUDES) -fsanitize=address -fsanitize=undefined

# Valgrind options (kept separate from CFLAGS)
VALGRIND = valgrind --leak-check=full --track-origins=yes --trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
--trace-children=yes --track-fds=yes --show-reachable=yes --suppressions=readline.sup

# Utilities
RM      = rm -f
AR      = ar rcs
MAKEFLAGS += --no-print-directory

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT   = ./libft
LIBS    = -lreadline

# Files
NAME    = minishell
SRC     = $(SRC_DIR)/minishell.c $(SRC_DIR)/minishell_utils.c $(SRC_DIR)/lexing/lexing.c \
			$(SRC_DIR)/lexing/lexing_functions.c 	$(SRC_DIR)/lexing/lexing_functions2.c \
			$(SRC_DIR)/lexing/tokenizing.c $(SRC_DIR)/lexing/qoutes_redirections.c $(SRC_DIR)/lexing/var_handler.c \
			$(SRC_DIR)/lexing/var_handler_utils.c $(SRC_DIR)/parsing/parsing.c $(SRC_DIR)/parsing/parsing_utils.c \
			$(SRC_DIR)/builtins/ft_cd.c $(SRC_DIR)/builtins/ft_echo.c $(SRC_DIR)/builtins/ft_env.c \
			$(SRC_DIR)/builtins/ft_export.c $(SRC_DIR)/builtins/ft_export_utils.c $(SRC_DIR)/builtins/ft_pwd.c \
			$(SRC_DIR)/env.c $(SRC_DIR)/env_utils.c $(SRC_DIR)/builtins/ft_unset.c\
      		$(SRC_DIR)/execution/execution.c 
		  


OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
LIBFT_A = $(LIBFT)/libft.a

# Colors
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
RED     = \033[1;31m
RESET   = \033[0m

# Default target
all: $(NAME)

# Create executable
$(NAME): $(OBJS) $(LIBFT_A)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Build libft
$(LIBFT_A):
	@echo "$(YELLOW)Building libft...$(RESET)"
	$(MAKE) -C $(LIBFT)

# Ensure obj directory and subdirectories exist, then compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/lexing  $(OBJ_DIR)/parsing $(OBJ_DIR)/builtins $(OBJ_DIR)/execution
	$(CC) $(CFLAGS) -c $< -o $@ 

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create lexing subdirectory under obj if it doesn't exist
$(OBJ_DIR)/lexing:
	mkdir -p $(OBJ_DIR)/lexing

# Create parsing subdirectory under obj if it doesn't exist
$(OBJ_DIR)/parsing:
	mkdir -p $(OBJ_DIR)/parsing

# Create builtins subdirectory under obj if it doesn't exist
$(OBJ_DIR)/builtins:
	mkdir -p $(OBJ_DIR)/builtins

# Create execution subdirectory under obj if it doesn't exist
$(OBJ_DIR)/execution:
	mkdir -p $(OBJ_DIR)/execution

# Run with Valgrind
run: $(NAME)
	@echo "$(YELLOW)Running with Valgrind...$(RESET)"
	$(VALGRIND) ./$(NAME)

# Debug build
debug: CFLAGS += -DDEBUG -fsanitize=address -g3
debug: re

# Clean object files only
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT) clean

# Clean all generated files
fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	@rm -rf $(OBJ_DIR)

# Rebuild everything
re: fclean all

# Declare that these targets are not files
.PHONY: all clean fclean re run debug
