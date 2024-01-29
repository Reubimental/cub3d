#ifndef CONSTANCE_H
# define CONSTANCE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "mlx.h"

# define	FLT_MAX 340282346638528859811704183484516925440.000000

# define	TILE_SIZE 64
# define	MAP_NUM_ROWS 11
# define	MAP_NUM_COLS 15

# define	MINIMAP_SCALE 0.2

# define	WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE) 
# define	WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define	FOV_ANGLE_workings_out (60 * (M_PI / 180)) 
# define	FOV_ANGLE 1.047197666666667

# define	NUM_RAYS WINDOW_WIDTH

# define	UP_ARROW 13
# define	S_KEY 1
# define	LEFT_ARROW 0
# define	RIGHT_ARROW 2
# define	ESC 53
# define    WIN_A 97
# define    WIN_S 115
# define    WIN_D 100
# define    WIN_W 119
# define    WIN_ESC 65307
# define    LINUX_A 28
# define    LINUX_S 30
# define    LINUX_D 31
# define    LINUX_W 17
# define    LINUX_ESC 1

# define	NORTH 1
# define	EAST 2
# define	SOUTH 3
# define	WEST 4

# define	CELING 5
# define	FLOOR 6

#endif