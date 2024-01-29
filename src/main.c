#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"

t_player player;

void	init_player()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 1;
	player.height = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = M_PI / 2;
	player.walkSpeed = 10;
	player.turnSpeed = M_PI / 180 * player.walkSpeed;
}

void	setup(char **argv1)
{
	// Add wall textrues here?
	init_player();
	(void)argv1;
//	init_texture_and_map(argv1);
}

void	safe_exit(t_game *game)
{
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
	if (game)
		free(game);
	exit(0);
}

void	movePlayer(t_game *game)
{
	if (!game)
		return ;
	player.rotationAngle += player.turnDirection * player.turnSpeed;
	float moveStep = player.walkDirection * player.walkSpeed;
	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;


	if (mapContentAt(newPlayerX, newPlayerY) != 1)
	{
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}


// 320 pixls window width
// 60 deg FOV -> must convert to rads
//
// while (column < 320width)
// {
// 	cast a ray
// 	trace the ray until it intersects with a wall (map[i][j] == 1)
// 	record the intersection x,y and ray distance
// 	add angle increment to go to the next ray (rayangle += 60/320) -> convert 60 deg into rads
// }




void	render(t_game *game)
{
	movePlayer(game);
	castAllRays();
	generate_3d_projection(game);
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	
	(void)argc;
	init_window(game);
	setup(&argv[1]);
	game->data = (t_data){0};
	game->data.img = mlx_new_image(game->mlx, WINDOW_WIDTH,  WINDOW_HEIGHT);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);


	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time. 
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
