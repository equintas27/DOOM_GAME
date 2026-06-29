/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:14:21 by equintas          #+#    #+#             */
/*   Updated: 2026/06/10 14:53:59 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_render(t_game *game)
{
	game->img = malloc_safe(sizeof(t_img),
			"Erro ao alocar memória para imagem");
	if (!game->img)
	{
		cleanup_game(game);
		exit(1);
	}
	game->img->img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img->img_ptr)
	{
		write(2, "Erro: Falha ao criar imagem MLX\n",
			ft_strlen("Erro: Falha ao criar imagem MLX\n"));
		cleanup_game(game);
		exit(1);
	}
	game->img->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp,
			&game->img->line_len, &game->img->endian);
	game->enemy_count = 0;
	get_enemy_position(game, '2');
}
