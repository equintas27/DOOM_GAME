/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 08:16:37 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/27 14:44:53 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}

void	free_datas(t_game *game)
{
	free_images(game);
	if (game->data)
	{
		if (game->data->north_path)
			free(game->data->north_path);
		if (game->data->south_path)
			free(game->data->south_path);
		if (game->data->west_path)
			free(game->data->west_path);
		if (game->data->east_path)
			free(game->data->east_path);
		if (game->data->floor_color)
			free(game->data->floor_color);
		if (game->data->ceiling_color)
			free(game->data->ceiling_color);
		free(game->data);
	}
}

void	aux_cleanup_game(t_game *game, int i)
{
	while (i < 5)
	{
		if (game->text[i].img)
			mlx_destroy_image(game->mlx, game->text[i].img);
		i++;
	}
	if (game->img)
	{
		if (game->img->img_ptr)
			mlx_destroy_image(game->mlx, game->img->img_ptr);
		free(game->img);
		game->img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	free_datas(game);
	if (game->map)
		free_map(game->map);
	if (game->door_frame)
		free_door_frames(game);
	if (game->file && game->file != game->map)
		free_split(game->file);
	aux_cleanup_game(game, i);
}
