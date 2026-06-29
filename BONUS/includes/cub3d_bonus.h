/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:29:51 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/29 10:25:16 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "parsing_bonus.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_door
{
	int						x;
	int						y;
	double					progress;
}							t_door;

typedef struct s_data		t_data;

typedef struct s_raycast	t_raycast;

typedef struct s_moves
{
	bool					forward;
	bool					backward;
	bool					m_left;
	bool					m_right;
	bool					r_left;
	bool					r_right;
}							t_moves;

typedef struct s_player
{
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
}							t_player;

typedef struct s_img
{
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
}							t_img;

typedef struct s_texture
{
	void					*img;
	char					*addr;
	int						width;
	int						height;
	int						bits_per_pixel;
	int						line_len;
	int						endian;
}							t_texture;

typedef struct s_enemy
{
	int						x;
	int						y;
	int						width;
	int						height;
	double					det;
	double					transform_x;
	double					transform_y;
	double					enemy_pos_x;
	double					enemy_pos_y;
	int						sprite_screen_x;
	int						sprite_h;
	int						sprite_w;
	int						draw_start_y;
	int						draw_end_y;
	int						draw_start_x;
	int						draw_end_x;
	int						color;
	int						visible;
}							t_enemy;

typedef struct s_game
{
	void					*mlx;
	void					*win;
	t_img					*img;
	t_enemy					enemies[100];
	int						enemy_count;
	t_img					*gamer_img;
	t_img					*enemy_img;
	char					**file;
	t_data					*data;
	t_texture				text[5];
	int						w;
	int						h;
	t_raycast				*vars;
	double					zbuffer[WIDTH];
	int						pos_x;
	t_moves					*moves;
	int						pos_y;
	int						n_player;
	char					**map;
	t_player				player;
	int						is_shooting;
	int						shot_anim_frame;
	int						**door_frame;
	int						door_anim_delay;
}							t_game;

typedef struct s_raycast
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					side_dist_x;
	double					side_dist_y;
	double					perp_wall_dist;
	int						map_pos_x;
	int						map_pos_y;
	int						step_x;
	int						step_y;
	int						side;
	int						x;
	int						y;
	int						hit;
	int						is_door;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						color;
	int						tex_num;
	int						tex_x;
	double					step;
	double					tex_pos;
}							t_raycast;

typedef struct s_weapon_vars
{
	int						x;
	int						y;
	int						color;
	int						center_x;
	int						start_y;
	int						end_y;
	int						current_y;
	int						local_cx;
	int						noise_x;
	int						thickness;
	int						x_offset;
	int						current_x;
	int						dist;
	int						size;
	int						s_y;
	int						s_x;
}							t_weapon_vars;

typedef struct s_shooter_vars
{
	double					ray_pos_x;
	double					ray_pos_y;
	double					ray_dir_x;
	double					ray_dir_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					side_dist_x;
	double					side_dist_y;
	int						map_x;
	int						map_y;
	int						step_x;
	int						step_y;
	int						hit;
}							t_shooter_vars;

void						init_player(t_game *game);
void						init_map(t_game *game);
void						cleanup_game(t_game *game);
void						*super_malloc(size_t bytes);
int							get_map_height(t_game *game);
void						get_player_position(t_game *game);

// HOOKS
int							mouse_hook(int x, int y, t_game *game);
int							close_window(t_game *game);
int							key_press(int key_press, t_game *game);
void						open_door_action(t_game *game);

// RENDER
void						my_mlx_put_img(t_img *img, int x, int y, int color);
void						init_render(t_game *game);
void						draw_background(t_game *game);
void						raycasting(t_game *game);
int							render_frame(void *param);
int							call_move_player(int keycode, t_game *game);
void						move_player_2(t_game *game, int dx, int dy);
void						rotate_right(t_game *game);
void						move_player(t_game *game, double dx, double dy);
void						rotate(t_game *game, double rot);
int							key_release(int key_release, t_game *game);
int							monitor_key(t_game *game);
void						draw_square(t_game *game, int x, int y, int color);
void						draw_minimap(t_game *game);
void						draw_direction(t_game *game);
void						calcul_perp_wall_dist(t_raycast *vars);
int							verify_side(t_raycast *vars);
int							get_texture_color(t_game *game, int tex_num,
								int tex_x, double tex_pos);
void						calcul_texture_vars(t_game *game, t_raycast *vars);
void						verify_tex_y(int *tex_y, int tex_height);
void						get_enemy_position(t_game *game, char enemy_char);
void						init_figures_pointer(t_img **img, t_game *game,
								char *img_path);
void						select_img(t_game *game, char **figure_buf);
void						draw_enemies(t_game *game, int i);
void						draw_weapon(t_game *game);
void						shoot_laser(t_game *game);

// TEXTURES
int							load_textures(t_game *game);

// UTILS
void						*malloc_safe(size_t bytes, char *str);

// DOOR
void						init_door_frames(t_game *game);
void						open_door_action(t_game *game);
void						update_door_animation(t_game *game);
int							is_door_passable(t_game *game, int x, int y);
void						free_door_frames(t_game *game);
#endif
