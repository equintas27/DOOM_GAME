# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: equintas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/23 13:11:47 by lkingui           #+#    #+#              #
#    Updated: 2026/06/27 14:59:17 by equintas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



Bonus = cub3D_bonus

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -Lminilibx-linux -Iminilibx-linux -lmlx_Linux -lXext -lX11 -lbsd
MLX_PATH = minilibx-linux/
MLX_LIB = $(MLX_PATH)libmlx_Linux.a
MLX_INC = -I$(MLX_PATH)
LIBFT_DIR = Mandatory/libft
LIBFT  = $(LIBFT_DIR)/libft.a

HEADER_BONUS = BONUS/includes/cub3d_bonus.h

RM = rm -f

BONUS_OBJS = BONUS/srcs/main_bonus.o \
     BONUS/srcs/render/render_init_bonus.o \
     BONUS/srcs/render/minimap_bonus.o \
     BONUS/srcs/render/render_utils_bonus.o \
     BONUS/srcs/render/render_bonus.o \
     BONUS/srcs/render/img_insertion.o \
     BONUS/srcs/render/raycasting_bonus.o \
     BONUS/srcs/utils/allocation_utils_bonus.o  \
     BONUS/srcs/utils/utils_bonus.o \
     BONUS/srcs/utils/frees_bonus.o \
     BONUS/srcs/hooks/key_hooks_bonus.o \
     BONUS/srcs/player/init_player_bonus.o \
     BONUS/srcs/parsing/utils_bonus.o \
     BONUS/srcs/parsing/checks_bonus.o \
     BONUS/srcs/parsing/checks2_bonus.o \
     BONUS/srcs/parsing/checks3_bonus.o \
     BONUS/srcs/parsing/checks4_bonus.o \
     BONUS/srcs/parsing/checks5_bonus.o \
     BONUS/srcs/parsing/copy_map_bonus.o \
     BONUS/srcs/parsing/count_lines_bonus.o \
     BONUS/srcs/parsing/read_map_bonus.o \
     BONUS/srcs/parsing/init_datas_bonus.o \
     BONUS/srcs/parsing/init_datas2_bonus.o \
     BONUS/srcs/parsing/flood_fill_bonus.o \
     BONUS/srcs/moves/moves_bonus.o \
     BONUS/gnl/get_next_line_bonus.o \
     BONUS/gnl/get_next_line_utils_bonus.o \
     BONUS/srcs/render/load_textures_bonus.o \
     BONUS/srcs/render/raycasting_utils_bonus.o \
     BONUS/srcs/hooks/door_operations_bonus.o \
     BONUS/srcs/hooks/door_operations_aux_bonus.o \
     BONUS/srcs/render/shooter_bonus.o

all: $(LIBFT) $(Bonus)

$(BONUS_OBJS): $(HEADER_BONUS)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_PATH)
    
$(NAME): $(BONUS_OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(BONUS_OBJS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT) -lm -o $(Bonus)
	@echo "Mandatory compilado com sucesso!"


clean:
	@$(RM) $(BONUS_OBJS)
	@echo "Cleaned!"
	@make clean -C $(LIBFT_DIR)
    
fclean: clean
	@$(RM) $(Bonus)
	@make fclean -C $(LIBFT_DIR)
    
re: fclean all

.PHONY: all clean fclean re bonus
