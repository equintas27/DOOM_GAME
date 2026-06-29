/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_insertion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:51:06 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/29 10:48:54 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_figures_pointer(t_img **img, t_game *game, char *img_path)
{
	int	w;
	int	h;

	*img = malloc(sizeof(t_img));
	if (!img)
	{
		write(2, "Error\nFail inserting the image!\n", 33);
		cleanup_game(game);
		exit(1);
	}
	(*img)->img_ptr = mlx_xpm_file_to_image(game->mlx, img_path, &w, &h);
	(*img)->addr = mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp,
			&(*img)->line_len, &(*img)->endian);
	game->enemies->width = w;
	game->enemies->height = h;
}

void	select_img(t_game *game, char **figure_buf)
{
	if (game->map[(int)game->player.pos_y][(int)game->player.pos_x] == 'N'
		|| game->map[(int)game->player.pos_y][(int)game->player.pos_x] == 'S'
		|| game->map[(int)game->player.pos_y][(int)game->player.pos_x] == 'E'
		|| game->map[(int)game->player.pos_y][(int)game->player.pos_x] == 'W')
		*figure_buf = game->gamer_img->addr;
	if (!*figure_buf)
	{
		write(2, "Error\nFail selecting the image!\n", 33);
		cleanup_game(game);
		exit(1);
	}
}
