/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:37:44 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/27 14:45:45 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_map(char **file, t_game *game, char *file_name)
{
	int	i;

	i = 0;
	while (file[i] && !is_first_map_line(file[i]))
		i++;
	if (!file[i])
		return (write(2, "Error\nMissing map!\n", 20), 0);
	game->map = copy_map(&file[i]);
	if (!game->map || !check_map_chars(game->map) || !check_map_content(game))
		return (0);
	if (is_map_at_middle_or_top(game->file, file_name))
		return (write(2, "Error\nMap in middle or in top\n", 31), 0);
	get_player_position(game);
	game->h = get_map_height(game);
	if (!check_flood_fill_result(game))
		return (0);
	return (1);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		cleanup_game(game);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		cleanup_game(game);
		exit(1);
	}
}

void	init_t_moves(t_moves *moves)
{
	moves->forward = false;
	moves->backward = false;
	moves->m_left = false;
	moves->m_right = false;
	moves->r_left = false;
	moves->r_right = false;
}

int	main(int ac, char *av[])
{
	t_game	game;
	t_moves	moves;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&moves, sizeof(t_moves));
	ac_check(ac, &game);
	check_extension(av[1]);
	game.file = read_map(av[1]);
	game.moves = &moves;
	init_t_moves(game.moves);
	if (!is_map(game.file, &game, av[1]))
		return (cleanup_game(&game), 1);
	init_door_frames(&game);
	init_data(&game, &game.data);
	check_all_file_lines(&game, game.data);
	init_mlx(&game);
	if (!load_textures(&game))
		return (cleanup_game(&game), 1);
	init_player(&game);
	init_figures_pointer(&game.gamer_img, &game, "textures/gamer.xpm");
	init_figures_pointer(&game.enemy_img, &game, "textures/captain.xpm");
	init_render(&game);
	mlx_loop_hook(game.mlx, &render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 6, (1L << 6), mouse_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	return (mlx_loop(game.mlx), cleanup_game(&game), 0);
}
