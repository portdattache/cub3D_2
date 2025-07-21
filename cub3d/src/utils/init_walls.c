/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:45 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 21:37:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Initialise la texture nord (NO)
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	init_tex_north(t_game *game)
{
	game->tex_north = malloc(sizeof(t_texture));
	if (!game->tex_north)
		return (print_error("malloc failed\n", 0));
	game->tex_north->is_init = 0;
	return (1);
}

/**
 * Initialise la texture sud (SO)
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	init_tex_south(t_game *game)
{
	game->tex_south = malloc(sizeof(t_texture));
	if (!game->tex_south)
	{
		free(game->tex_north);
		return (print_error("malloc failed\n", 0));
	}
	game->tex_south->is_init = 0;
	return (1);
}

/**
 * Initialise la texture est (EA)
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	init_tex_east(t_game *game)
{
	game->tex_east = malloc(sizeof(t_texture));
	if (!game->tex_east)
	{
		free(game->tex_north);
		free(game->tex_south);
		return (print_error("malloc failed\n", 0));
	}
	game->tex_east->is_init = 0;
	return (1);
}

/**
 * Initialise la texture ouest (WE)
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	init_tex_west(t_game *game)
{
	game->tex_west = malloc(sizeof(t_texture));
	if (!game->tex_west)
	{
		free(game->tex_north);
		free(game->tex_south);
		free(game->tex_east);
		return (print_error("malloc failed\n", 0));
	}
	game->tex_west->is_init = 0;
	return (1);
}
