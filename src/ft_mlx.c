#include "../inc/ft_mlx.h"
#include "../inc/constance.h"

extern t_player player;

int	key_release(int keycode)
{
	if (keycode == LEFT_ARROW || keycode == LINUX_A || keycode == WIN_A)
		player.turnDirection = 0;
	else if (keycode == RIGHT_ARROW || keycode == LINUX_D || keycode == WIN_D)
		player.turnDirection = 0;
	else if (keycode == UP_ARROW || keycode == LINUX_W || keycode == WIN_W)
		player.walkDirection = 0;
	else if (keycode == S_KEY || keycode == LINUX_S || keycode == WIN_S)
		player.walkDirection = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW || keycode == LINUX_A || keycode == WIN_A)
		player.turnDirection = -1;
	else if (keycode == RIGHT_ARROW || keycode == LINUX_D || keycode == WIN_D)
		player.turnDirection = 1;
	else if (keycode == UP_ARROW || keycode == LINUX_W || keycode == WIN_W)
		player.walkDirection = 1;
	else if (keycode == S_KEY || keycode == LINUX_S || keycode == WIN_S)
		player.walkDirection = -1;
	else if (keycode == ESC || keycode == LINUX_ESC || keycode == WIN_ESC)
		safe_exit(game);
	// renderPlayer(game);
	// movePlayer(game);
	// renderMap(game);
	// renderPlayer(game);
	render(game);
	return (0);
}

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		safe_exit(game);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_release, game);

	return (true);
}