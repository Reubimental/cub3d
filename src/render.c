#include "../inc/render.h"
#include "../inc/draw.h"
#include "../inc/constance.h"
#include "../inc/cub3d.h"
#include "../inc/ray.h"

extern t_player player;

void	render_player(t_game *game)
{
	t_rectangle player_rect;
	t_line player_line;

	player_rect.x = player.x * MINIMAP_SCALE;
	player_rect.y = player.y * MINIMAP_SCALE;
	player_rect.width = player.width * MINIMAP_SCALE;
	player_rect.height = player.height * MINIMAP_SCALE;
	player_rect.color =	0x00E0B0FF;

	draw_rect(game, &player_rect);

	player_line.x0 = player.x * MINIMAP_SCALE;
	player_line.y0 = player.y * MINIMAP_SCALE;
	player_line.x1 = (player.x + cos(player.rotationAngle) * 40) * MINIMAP_SCALE;
	player_line.y1 = (player.y + sin(player.rotationAngle) * 40) * MINIMAP_SCALE;
	player_line.color =	0x00E0B0FF;

	draw_line(game, &player_line);
}

void draw_ceiling(t_game *game)
{
	t_rectangle ceiling;
	t_rectangle floor;

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.width = WINDOW_WIDTH;
	ceiling.height = WINDOW_HEIGHT / 2;
	ceiling.color = 0x00FAF0E6;

	draw_rect(game, &ceiling);

	floor.x = 0;
	floor.y = WINDOW_HEIGHT / 2;
	floor.width = WINDOW_WIDTH;
	floor.height = WINDOW_HEIGHT / 2;
	floor.color = 0x008B9E8A;

	draw_rect(game, &floor);
}

void	generate_3d_projection(t_game *game)
{
	draw_ceiling(game);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		float correctedDistance = rays[i].distance * cos(rays[i].rayAngle - player.rotationAngle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / correctedDistance) * distanceProjPlane;
		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallTopPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		int _color;
		if (rays[i].isRayFacingDown && !rays[i].wasHitVertical)
			_color = 0x0000FFFF;
		if (rays[i].isRayFacingUp && !rays[i].wasHitVertical)
			_color = 0x00FFFF00;
		if (rays[i].isRayFacingLeft && rays[i].wasHitVertical)
			_color = 0x00FF00FF;
		if (rays[i].isRayFacingRight && rays[i].wasHitVertical)
			_color = 0x0000FF00;
		t_rectangle rect = {
			.x = i,
			.y = WINDOW_HEIGHT / 2 - wallStripHeight / 2, 
			.width = 1,
			.height = wallStripHeight,
			.color = _color
		};

		draw_rect(game, &rect);
	}
}