/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:37:44 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/29 10:51:28 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	error_msg(void)
{
	write(2, "Error\nThe file does not exist!\n", 32);
	exit(1);
	return (0);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->text[i].img)
		{
			mlx_destroy_image(game->mlx, game->text[i].img);
			game->text[i].img = NULL;
		}
		i++;
	}
}

void	free_images(t_game *game)
{
	free_textures(game);
	if (!game || !game->mlx)
		return ;
	if (game->gamer_img && game->gamer_img->img_ptr)
	{
		mlx_destroy_image(game->mlx, game->gamer_img->img_ptr);
		game->gamer_img->img_ptr = NULL;
	}
	if (game->enemy_img && game->enemy_img->img_ptr)
	{
		mlx_destroy_image(game->mlx, game->enemy_img->img_ptr);
		game->enemy_img->img_ptr = NULL;
	}
	if (game->gamer_img)
		free(game->gamer_img);
	if (game->enemy_img)
		free(game->enemy_img);
}
