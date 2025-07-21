/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:51:25 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 02:54:40 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si une position est bloquée (mur ou bordure)
 * @param game structure principale du jeu
 * @param x coordonnée x de la position à tester
 * @param y coordonnée y de la position à tester
 * @return 1 si bloqué, 0 sinon
 */
static int	is_position_blocked(t_game *game, int x, int y)
{
	if (is_blocking_up(game, x, y))
		return (1);
	if (is_blocking_down(game, x, y))
		return (1);
	if (is_blocking_right(game, x, y))
		return (1);
	if (is_blocking_left(game, x, y))
		return (1);
	return (0);
}

/**
 * Déplace le joueur vers l'avant
 * @param game structure principale du jeu
 */
void	move_player_forward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.map_pos.x + cos(game->player.dir) * game->player.speed;
	ny = game->player.map_pos.y + sin(game->player.dir) * game->player.speed;
	if (!is_position_blocked(game, nx, ny))
	{
		game->player.map_pos.x = nx;
		game->player.map_pos.y = ny;
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
	draw_frame(game);
}

/**
 * Déplace le joueur vers l'arrière
 * @param game structure principale du jeu
 */
void	move_player_backward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.map_pos.x - cos(game->player.dir) * game->player.speed;
	ny = game->player.map_pos.y - sin(game->player.dir) * game->player.speed;
	if (!is_position_blocked(game, nx, ny))
	{
		game->player.map_pos.x = nx;
		game->player.map_pos.y = ny;
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
	draw_frame(game);
}

/**
 * Déplace le joueur vers la gauche (strafe gauche)
 * @param game structure principale du jeu
 */
void	move_player_left(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x - cos(game->player.dir + M_PI_2) * s;
	ny = game->player.map_pos.y - sin(game->player.dir + M_PI_2) * s;
	if (!is_position_blocked(game, nx, ny))
	{
		game->player.map_pos.x = nx;
		game->player.map_pos.y = ny;
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
	draw_frame(game);
}

/**
 * Déplace le joueur vers la droite (strafe droite)
 * @param game structure principale du jeu
 */
void	move_player_right(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x + cos(game->player.dir + M_PI_2) * s;
	ny = game->player.map_pos.y + sin(game->player.dir + M_PI_2) * s;
	if (!is_position_blocked(game, nx, ny))
	{
		game->player.map_pos.x = nx;
		game->player.map_pos.y = ny;
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
	draw_frame(game);
}
