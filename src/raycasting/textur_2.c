
#include "../../include/cub3D.h"


/* ========== FONCTION 2: Calculer les dimensions du mur ========== */

static void	init_render_data(t_map *map, t_dda *dda, t_textur *tex, t_render *r)
{
	r->line_height = (int)(map->screen_height / dda->perp_wall_dist);
	if (r->line_height <= 0)
		r->line_height = 1;
	r->draw_start = map->screen_height / 2 - r->line_height / 2;
	r->draw_end = r->line_height / 2 + map->screen_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= map->screen_height)
		r->draw_end = map->screen_height - 1;
	r->ceiling_color = map->color_ceil;
	r->floor_color = map->color_floor;
	r->tex_x = calcul_position_texture(dda, map, tex);
	r->step = (double)tex->textur_height / (double)r->line_height;
	r->tex_pos = (r->draw_start - map->screen_height / 2 + r->line_height / 2)
		* r->step;
}

/* ========== FONCTION 3: Dessiner la texture du mur ========== */

static void	draw_wall_texture(int x, t_map *map, t_textur *tex, t_render *r)
{
	int		y;
	int		tex_y;
	int		color;
	char	*pixel;

	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->textur_height)
			tex_y = tex->textur_height - 1;
		r->tex_pos += r->step;
		pixel = tex->addr + tex_y * tex->length_line + r->tex_x
			* (tex->bits_per_pxl / 8);
		color = *(int *)pixel;
		put_pixel(map, x, y, color);
		y++;
	}
}

/* ========== FONCTION 4: Dessiner plafond et sol ========== */

static void	draw_ceiling_floor(int x, t_map *map, t_render *r)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
	{
		put_pixel(map, x, y, r->ceiling_color);
		y++;
	}
	y = r->draw_end + 1;
	while (y < map->screen_height)
	{
		put_pixel(map, x, y, r->floor_color);
		y++;
	}
}

/* ========== FONCTION PRINCIPALE ========== */

void	render_column_textured(int x, t_map *map, t_dda *dda, t_textur *tex)
{
	t_render	r;

	if (!tex || !tex->addr)
		return ;
	init_render_data(map, dda, tex, &r);
	draw_ceiling_floor(x, map, &r);
	draw_wall_texture(x, map, tex, &r);
}
