- Make const int map into file and then struct. 

Make vert and horiz cast_one_ray() components structs to pass into a new compare function. 

# Sort out. or: remove as globals
int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
Player {
Ray {

# Move functions into seperate files

## Main
main(void)
render(t_game \*game) *It's a bad name*
safe_exit(t_game *game)

## Init
setup() — must change


## Ray
cast_one_ray(float ray_angle, int stripId)
renderRays(t_game \*game) can remove
generate_3d_projection(t_game \*game) *because it has the rays[] struct*

## Player
movePlayer(t_game *game)




# Sorted, so far...

## Mlx
init_window(t_game *game)
key_hook(int keycode, t_game *game)
key_release(int keycode)

## Maths
normalizeAngle(float ray_angle)
istanceBetweenPoints(float x1, float y1, float x2, float y2)

## Map
renderMap(t_game *game)
mapContentAt(float x, float y)

## Render
renderPlayer(t_game *game)
drawCeling(t_game *game)

## Render utils
draw_rect(t_game *game, t_rectangle *rect)
draw_line(t_game *game, t_line *line) {


