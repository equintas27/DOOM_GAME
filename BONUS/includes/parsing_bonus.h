/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:44:08 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/29 10:43:29 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_game	t_game;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
	int					combined;
}						t_color;

typedef struct s_data
{
	char				*north_path;
	char				*south_path;
	char				*west_path;
	char				*east_path;
	t_color				*floor_color;
	t_color				*ceiling_color;
	int					ceiling_color_pos;
	int					floor_color_pos;
	int					count_ceiling_colors;
	int					count_floor_colors;
	int					count_textures;
}						t_data;

char					*get_next_line(int fd);
char					*extract_line(char *stash);
char					*copy_line(char *line);
char					**copy_map(char **map);
void					free_map(char **map);
int						ac_check(int ac, t_game *game);
char					**read_map(char *file);
int						count_lines(int fd);
void					check_extension(char *file);
int						extension(char *file);
int						error_msg(void);
void					init_data(t_game *game, t_data **data);
void					init_data_struct(t_data **data);
void					free_split(char **split);
void					free_datas(t_game *game);
void					free_images(t_game *game);
void					free_textures(t_game *game);
int						is_map_line(char *line);
void					check_limit_rgb(t_data *data, t_game *game,
							char **file);
void					print_datas(t_data *data);
void					check_textures_extension(t_data *data, t_game *game,
							char **file);
int						is_map_at_middle_or_top(char **file, char *file_name);
int						ft_isempty_line(char *line);
int						count_lines(int fd);
int						validate_rgb(char **splited);
void					check_valid_datas(char **splited, t_game *game,
							t_data *data, char **file);
int						check_map_chars(char **map);
int						check_map_content(t_game *game);
int						check_first_and_last_line(char **map, t_game *game);
void					check_colors_number(t_data *data, t_game *game);
void					check_textures_number(t_data *data, t_game *game);
int						is_first_map_line(char *line);
int						check_flood_fill_result(t_game *game);
int						check_texture_extension(char *file);
void					check_all_file_lines(t_game *game, t_data *data);
void					init_ceiling_colors(t_game *game, char **file,
							t_data *data);
void					init_floor_colors(t_game *game, char **file,
							t_data *data);
void					init_count_colors(t_data *data, char **file);
void					init_floor_colors(t_game *game, char **file,
							t_data *data);
void					init_ceiling_colors(t_game *game, char **file,
							t_data *data);
void					init_textures_aux(t_data **data, t_game *game, int i,
							int j);
void					init_textures(t_data **data, t_game *game, int i,
							int j);
void					check_invalid_colors_separation(t_data *data,
							char **file, t_game *game);
void					check_invalid_texture_separation(t_data **data,
							t_game *game, int i);

#endif
