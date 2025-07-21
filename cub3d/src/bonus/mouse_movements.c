/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:15:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/07/21 23:00:33 by broboeuf         ###   ########.fr       */
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

int	on_focus_in(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->win);
	return (0);
}

int	on_focus_out(t_game *game)
{
	mlx_mouse_show(game->mlx, game->win);
	return (0);
}
void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 9, (1L << 21), on_focus_in, game);
	mlx_hook(game->win, 10, (1L << 3), on_focus_out, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keys, game);
	mlx_hook(game->win, 17, (1L << 2), free_game, game);
	mlx_loop_hook(game->mlx, update_game, game);
}

int	handle_focus_in(t_game *game)
{
	game->has_focus = 1;
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	handle_focus_out(t_game *game)
{
	game->has_focus = 0;
	mlx_mouse_show(game->mlx, game->win);
	return (0);
}
