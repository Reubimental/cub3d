#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

t_ray	g_rays[NUM_RAYS];

void	calculate_steps(float ray_angle, float *xstep, float *ystep, char axis)
{
	if (axis == 'x')
	{
		*ystep = TILE_SIZE;
		if (is_ray_facing_up(ray_angle))
			*ystep *= -1;
		*xstep = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_left(ray_angle) && *xstep > 0)
			*xstep *= -1;
		if (is_ray_facing_right(ray_angle) && *xstep < 0)
			*xstep *= -1;
	}
	if (axis == 'y')
	{
		*xstep = TILE_SIZE;
		if (is_ray_facing_left(ray_angle))
			*xstep *= -1;
		*ystep = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_up(ray_angle) && *ystep > 0)
			*ystep *= -1;
		if (is_ray_facing_down(ray_angle) && *ystep < 0)
			*ystep *= -1;
	}
}

void	cast_one_ray(float ray_angle, int stripId,
			t_wall_hit *vertical, t_wall_hit *horizontal)
{
	float		vert_hit_distance;
	float		horz_hit_distance;

	normalize_angle(&ray_angle);
	horizontal_intersection(&horizontal, ray_angle);
	vertical_intersection(&vertical, ray_angle);
	if (horizontal.found_wall_hit)
		horz_hit_distance = distance_between_points(t_player.x, t_player.y,
				horizontal.wall_hit_x, horizontal.wall_hit_y);
	else
		horz_hit_distance = FLT_MAX;
	if (vertical.found_wall_hit)
		vert_hit_distance = distance_between_points(t_player.x, t_player.y,
				vertical.wall_hit_x, vertical.wall_hit_y);
	else
		vert_hit_distance = FLT_MAX;
	if (vert_hit_distance < horz_hit_distance)
		ray_cast(&vertical, stripId, ray_angle, vert_hit_distance);
	else
		ray_cast(&horizontal, stripId, ray_angle, horz_hit_distance);
}

void	ray_cast(t_wall_hit *hit, int stripId,
			float ray_angle, float hit_distance)
{
	g_rays[stripId].distance = hit_distance;
	g_rays[stripId].wall_hit_x = hit->wall_hit_x;
	g_rays[stripId].wall_hit_y = hit->wall_hit_y;
	g_rays[stripId].wall_hit_content = hit->wall_content;
	g_rays[stripId].was_hit_vertical = hit->is_vertical;
	g_rays[stripId].ray_angle = ray_angle;
	g_rays[stripId].is_ray_facing_down = is_ray_facing_down(ray_angle);
	g_rays[stripId].is_ray_facing_up = is_ray_facing_up(ray_angle);
	g_rays[stripId].is_ray_facing_left = is_ray_facing_left(ray_angle);
	g_rays[stripId].is_ray_facing_right = is_ray_facing_right(ray_angle);
}

void	cast_all_rays(void)
{
	int		strip_id;
	float	ray_angle;
	t_wall_hit	horizontal;
	t_wall_hit	vertical;

	wall_hit_params(&horizontal);
	wall_hit_params(&vertical);
	strip_id = 0;
	ray_angle = t_player.rotation_angle - FOV_ANGLE / 2;
	while (strip_id < NUM_RAYS)
	{
		horizontal.found_wall_hit = false;
		vertical.found_wall_hit = false;
		cast_one_ray(ray_angle, strip_id, &vertical, &horizontal);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
}
	// printf("FOV: %f StripId: %d ray_angle: %f\n", FOV_ANGLE, stripId, ray_angle);

void	render_rays(t_game *game)
{
	int		i;
	t_line	line;

	i = -1;
	while (++i < NUM_RAYS)
	{
		line.x0 = t_player.x * MINIMAP_SCALE;
		line.y0 = t_player.y * MINIMAP_SCALE;
		line.x1 = g_rays[i].wall_hit_x * MINIMAP_SCALE;
		line.y1 = g_rays[i].wall_hit_y * MINIMAP_SCALE;
		line.color = 0x00FFC8D7;
		draw_line(game, &line);
	}
}
