/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:15:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/07/20 00:28:25 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Fonction qui va gerer les mouvements de l'axe de vision par la souris
// et regle la vitesse de rotation
int	update_game(t_game *game)
{
	int		mouse_x;
	int		mouse_y;
	int		center_x;
	double	angle;
	double	rot_speed;

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
