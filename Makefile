NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Dossiers
SRC_DIR     = src
INC_DIR     = includes
LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

# Sources
SRC         = $(SRC_DIR)/main.c \
              $(SRC_DIR)/read_files.c \
              $(SRC_DIR)/get_next_line.c \
              $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/line_utils.c \
			  $(SRC_DIR)/map_utils.c \
              $(SRC_DIR)/parse_lines.c \
			  $(SRC_DIR)/parse_file.c \
			  $(SRC_DIR)/parse_color.c \
			  $(SRC_DIR)/parse_map.c \
			  $(SRC_DIR)/map_validation.c \
			  $(SRC_DIR)/check_open_spaces.c \
			  $(SRC_DIR)/map_format.c \
			  $(SRC_DIR)/player_init.c \
			  $(SRC_DIR)/map_flood_fill.c \
			  $(SRC_DIR)/free_config.c \


OBJ         = $(SRC:.c=.o)

# Compilation finale
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -I$(INC_DIR) -o $(NAME)

# Compilation générique des .o avec includes/
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compiler libft automatiquement
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
