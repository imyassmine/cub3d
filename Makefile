################################################################################
#                                     COLORS                                   #
################################################################################

DEFAULT			= \033[0m
RED				= \033[1;31m
GREEN			= \033[1;32m
YELLOW			= \033[1;33m
BLUE			= \033[1;34m
MAGENTA			= \033[1;35m
CYAN			= \033[1;36m
LIGHT_CYAN		= \033[1;96m
WHITE			= \033[1;37m

################################################################################
#                                     HEADER                                   #
################################################################################

define HEADER

	$(CYAN)╔═══════ $(WHITE)by yaabdall & cldalmaz$(CYAN) ══════════════════════════╗$(DEFAULT)
	$(CYAN)║                                                         ║$(DEFAULT)
	$(CYAN)║                                                         ║$(DEFAULT)
	$(CYAN)║                                                         ║$(DEFAULT)
	$(LIGHT_CYAN)║         ______   __  __    ____    _____    ____        ║$(DEFAULT)
	$(LIGHT_CYAN)║        / ____/  / / / /   / __ )  |__  /   / __ \       ║$(DEFAULT)
	$(LIGHT_CYAN)║       / /      / / / /   / __  |   /_ <   / / / /       ║$(DEFAULT)
	$(LIGHT_CYAN)║      / /___   / /_/ /   / /_/ /  ___/ /  / /_/ /        ║$(DEFAULT)
	$(LIGHT_CYAN)║      \____/   \____/   /_____/  /____/  /_____/         ║$(DEFAULT)     
	$(WHITE)║                                                         ║$(DEFAULT)
	$(WHITE)║                                                         ║$(DEFAULT)
	$(WHITE)║                                                         ║$(DEFAULT)
	$(WHITE)╚══════════════════════════ $(CYAN)by cldalmaz & yaabdall$(WHITE) ═══════╝$(DEFAULT)

endef
export HEADER

################################################################################
#                                 PROGRESS BAR                                 #
################################################################################

define PROGRESS_BAR
    @TOTAL_STEPS=20; CURRENT_STEP=0; \
    while [ $$CURRENT_STEP -lt $$TOTAL_STEPS ]; do \
        CURRENT_STEP=$$(($$CURRENT_STEP + 1)); \
        echo -n "$(GREEN)▰$(DEFAULT)"; \
        sleep 0.01; \
    done; \
    echo " ✔️";
endef

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME =			cub3D
NAME_BONUS =	cub3D_bonus
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs
RM =			rm -f

################################################################################
#                                PROGRAM'S SOURCES                             #
################################################################################

# Directory paths
SRC =			./srcs/
PARSING =		$(SRC)parsing/
EXEC =			$(SRC)exec/
OBJ =			./objs/
MYLIB_DIR =		./my_lib/
MLX_DIR =		./mlx
INCLUDES =		./includes/ $(MYLIB_DIR)includes/ $(MLX_DIR)

# Libraries
MYLIB =			-L $(MYLIB_DIR) -l:my_lib.a
MLX =			-L $(MLX_DIR) -l:libmlx.a -lXext -lX11 -lm

# Source files
SRCX =			$(PARSING)parsing.c \
				$(EXEC)exec.c \
				$(SRC)utils.c \

SRCS =			$(SRCX) \
				$(SRC)main.c

SRCS_BONUS =	$(SRCX) \
				$(SRC)main_bonus.c

# Converts source file paths to object file paths
OBJS =			$(patsubst $(SRC)%, $(OBJ)%, $(SRCS:.c=.o))
OBJS_BONUS =	$(patsubst $(SRC)%, $(OBJ)%, $(SRCS_BONUS:.c=.o))

################################################################################
#                                     RULES                                    #
################################################################################

# Rule for compiling source files into object files
$(OBJ)%.o:		$(SRC)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(foreach dir,$(INCLUDES),-I$(dir))

# Rule for creating the executable
$(NAME):		$(OBJS)
				@make all --no-print-directory -C $(MYLIB_DIR)
				@echo "$(WHITE)Building $(YELLOW)mlx $(CYAN)library $(DEFAULT)..."
				@make all --no-print-directory -C $(MLX_DIR)
				@echo -n "\n🔗 $(WHITE)Linking $(CYAN)$(NAME)$(DEFAULT) executable\t\t\t"
				@$(CC) $(CFLAGS) $(OBJS) $(MYLIB) $(MLX) -o $(NAME)
				$(PROGRESS_BAR)
				@echo "\n$$HEADER"

# Default rule
all:			$(NAME)

# Bonus rule
bonus:			$(OBJS_BONUS)
				@make all --no-print-directory -C $(MYLIB_DIR)
				@echo -n "\n🔗 $(WHITE)Linking $(CYAN)$(NAME_BONUS)$(DEFAULT) executable\t\t"
				@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MYLIB) -o $(NAME_BONUS)
				$(PROGRESS_BAR)
				@echo "\n$$HEADER"

# Rule for cleaning up object files
clean:
				@make clean --no-print-directory -C $(MYLIB_DIR)
				@echo -n "\n🧹 $(RED)Cleaning up$(DEFAULT) project object files\t\t"
				@$(RM) -r $(OBJ)
				$(PROGRESS_BAR)
				@echo ""

# Full clean rule (objects files, executable and libraries)
fclean:
				@make fclean --no-print-directory -C $(MYLIB_DIR)
				@echo -n "\n🧹 $(RED)Cleaning up$(DEFAULT) $(CYAN)$(NAME)$(DEFAULT) object files\t\t"
				@$(RM) -r $(OBJ)
				$(PROGRESS_BAR)
				@echo -n "\n🗑️  $(RED)Deleting $(CYAN)$(NAME)$(DEFAULT) executable\t\t"
				@$(RM) $(NAME) $(NAME_BONUS)
				$(PROGRESS_BAR)
				@echo ""

# Rebuild rule
re:				fclean all

# Rule to compile the program with debugging flags
debug:			$(OBJS)
				@make all --no-print-directory -C $(MYLIB_DIR)
				@echo -n "\n🔗 $(CYAN)Compiling in debug mode $(DEFAULT)\t\t\t"
				@$(CC) $(CFLAGS) $(OBJS) $(MYLIB) -o $(NAME) -g3 -fsanitize=address
				$(PROGRESS_BAR)
				@echo "$$HEADER"

# Rule to display help
help:
				@echo "\n$(CYAN)all$(DEFAULT)		- Build the executable $(NAME)"
				@echo "$(CYAN)bonus$(DEFAULT)		- Build the executable $(NAME_BONUS)"
				@echo "$(CYAN)clean$(DEFAULT)		- Clean up object files"
				@echo "$(CYAN)fclean$(DEFAULT)		- Clean up all object files and executables"
				@echo "$(CYAN)re$(DEFAULT)		- Rebuild the entire project"
				@echo "$(CYAN)debug$(DEFAULT)		- Run the program with debugging flags -g3\n"

# Rule to ensure that these targets are always executed as intended, even if there are files with the same name
.PHONY:			all bonus clean fclean re debug help
