/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:43:39 by                   #+#    #+#             */
/*   Updated: 2022/01/25 14:33:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3.h"

t_panel	ft_init_panel(t_game *game)
{
	t_panel	panel;

	panel.width = game->scrn_wdth;
	panel.hight = game->scrn_hght;
	panel.line_size = 0;
	panel.bit_per_px = 0;
	panel.end = 0;
	panel.ref = mlx_new_image(game->mlx, panel.width, panel.hight);
	panel.addr = mlx_get_data_addr(panel.ref, &(panel.bit_per_px),
			&(panel.line_size), &(panel.end));
	return (panel);
}
