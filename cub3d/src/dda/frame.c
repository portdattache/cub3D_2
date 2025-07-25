/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:41:40 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/24 00:57:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Dessine l’image complète colonne par colonne
 * Chaque rayon génère deux colonnes de pixels (2x NB_RAYS)
 * @param game structure principale du jeu
 */
static void	draw_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_RAYS)
	{
		if (game->rays[i].distance > 0)
		{
			draw_slice(game, game->rays[i], 2 * i);
			draw_slice(game, game->rays[i], 2 * i + 1);
		}
		i++;
	}
}

/**
 * Lance NB_RAYS rayons depuis la position du joueur
 * Utilise la fonction de DDA pour détecter les murs
 * Les résultats sont stockés dans game->rays
 * @param game structure principale
 */
static void	raycasting(t_game *game)
{
	int		i;
	double	ray_angle;

	if (game->rays)
		free(game->rays);
	game->rays = malloc(sizeof(t_ray) * NB_RAYS);
	if (!game->rays)
	{
		print_error("malloc failed\n", 0);
		free_game(game);
	}
	ray_angle = game->player.dir - (HALF_FOV * DEG_RAD);
	ray_angle = normalize_angle(ray_angle);
	i = -1;
	while (++i < NB_RAYS)
	{
		cast_ray(game, ray_angle, &game->rays[i]);
		ray_angle += ANGLE_INCR;
		ray_angle = normalize_angle(ray_angle);
	}
}

/**
 * Génère et affiche une frame complète du jeu
 * @param game structure principale
 */
void	draw_frame(t_game *game)
{
	if (game->screen.img)
	{
		mlx_destroy_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	game->screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen.img)
		free_game(game);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		free_game(game);
	raycasting(game);
	draw_image(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}

// Fonction qui va gerer les mouvements de l'axe de vision par la souris
// et regle la vitesse de rotation
int	update_game(t_game *game)
{
	int		mouse_x;
	int		mouse_y;
	int		center_x;
	double	angle;
	double	rot_speed;

	if (!game->has_focus)
		return (0);
	center_x = WIDTH / 2;
	rot_speed = 0.003;
	mlx_mouse_get_pos(game->mlx, game->win, &mouse_x, &mouse_y);
	if (mouse_x != center_x)
	{
		angle = (mouse_x - center_x) * rot_speed;
		game->player.dir += angle;
		if (game->player.dir < 0)
			game->player.dir += 2 * M_PI;
		else if (game->player.dir >= 2 * M_PI)
			game->player.dir -= 2 * M_PI;
		mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	}
	draw_frame(game);
	return (0);
}
