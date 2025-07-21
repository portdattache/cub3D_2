/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:28:02 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 21:19:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Charge une texture depuis un fichier .xpm
 * @param game Structure principale contenant le contexte MLX
 * @param tex Texture à remplir
 * @param path Chemin vers le fichier .xpm
 * @return 1 en cas de succès, 0 sinon
 */
int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (print_error("texture not found\n", 0));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (print_error("texture addr not found\n", 0));
	return (1);
}

/**
 * Récupère la couleur d'un pixel d'une texture
 * @param tex Texture source
 * @param x Coordonnée X du pixel
 * @param y Coordonnée Y du pixel
 * @return Couleur du pixel au format int
 */
int	get_tex_color(t_texture *tex, int x, int y)
{
	int	offset;

	if (x < 0 || x >= tex->width)
		return (0);
	if (y < 0 || y >= tex->height)
		return (0);
	offset = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->addr + offset));
}

/**
 * Crée une couleur au format MLX
 * @param t Transparence
 * @param r Rouge
 * @param g Vert
 * @param b Bleu
 * @return Couleur encodée au format MLX
 */
int	create_color(int t, int r, int g, int b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

/**
 * Gère les actions clavier pendant la partie
 * @param key Touche pressée
 * @param game Structure du jeu
 * @return 0
 */
static int	handle_keys(int key, t_game *game)
{
	if (key == LEFT_ARROW || key == RIGHT_ARROW)
	{
		if (key == LEFT_ARROW)
			game->player.dir -= ROT_SPEED;
		else
			game->player.dir += ROT_SPEED;
		game->player.dir = normalize_angle(game->player.dir);
		draw_frame(game);
	}
	else if (key == FORWARD)
		move_player_forward(game);
	else if (key == BACKWARD)
		move_player_backward(game);
	else if (key == LEFT)
		move_player_left(game);
	else if (key == RIGHT)
		move_player_right(game);
	if (key == ESC)
		free_game(game);
	return (0);
}

/**
 * Démarre la boucle principale du jeu avec les hooks MLX
 * @param game Structure du jeu
 */
void	game_loop(t_game *game)
{
	mlx_do_key_autorepeaton(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, handle_keys, game);
	mlx_hook(game->win, 17, (1L << 2), free_game, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(game->mlx, update_game, game);
	draw_frame(game);
	mlx_loop(game->mlx);
}
