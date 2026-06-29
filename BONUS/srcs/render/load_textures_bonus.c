/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:35 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 10:45:59 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	load_textures(t_game *game)
{
	char	*txt_path[5];
	int		i;

	txt_path[0] = game->data->north_path;
	txt_path[1] = game->data->south_path;
	txt_path[2] = game->data->west_path;
	txt_path[3] = game->data->east_path;
	txt_path[4] = "textures/wolfenstein/wood.xpm";
	i = 0;
	while (i < 5)
	{
		game->text[i].img = mlx_xpm_file_to_image(game->mlx, txt_path[i],
				&game->text[i].width, &game->text[i].height);
		if (!game->text[i].img)
		{
			printf("Error with texture\n");
			return (0);
		}
		game->text[i].addr = mlx_get_data_addr(game->text[i].img,
				&game->text[i].bits_per_pixel, &game->text[i].line_len,
				&game->text[i].endian);
		i++;
	}
	return (1);
}
