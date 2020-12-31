#include "render.h"


/* Draw Sprite */

/**
 * Where x and y are normalised coordinates for sprite.
 *
 *        +1.0f
 *          |
 * 0.0f <- 0.5f -> +1.0f
 *          |
 *         0.0f
 */
static uint32 sprite_image_lookup(const struct Sprite_Image* sprite_image, float xf, float yf)
{
	xf = clamp(xf, 0.0f, 1.0f);
	yf = clamp(yf, 0.0f, 1.0f);

	const int x = xf * (float)sprite_image->bi_width;
	const int y = yf * (float)sprite_image->bi_height;

	const uint bytes_per_pixel = sprite_image->bi_bit_count / 8;

	const uint32 r = ((uint32)(sprite_image->pdata[(x * bytes_per_pixel) + (y * sprite_image->bi_width * bytes_per_pixel) + 0]) << 16);
	const uint32 g = ((uint32)(sprite_image->pdata[(x * bytes_per_pixel) + (y * sprite_image->bi_width * bytes_per_pixel) + 1]) << 8);
	const uint32 b = ((uint32)(sprite_image->pdata[(x * bytes_per_pixel) + (y * sprite_image->bi_width * bytes_per_pixel) + 2]) << 0);
	uint32 a;
	if (bytes_per_pixel == 4)
	{
		a = ((uint32)(sprite_image->pdata[(x * bytes_per_pixel) + (y * sprite_image->bi_width * bytes_per_pixel) + 3]) << 24);
	}
	else
	{
		a = 0xff000000;
	}

	return (
		a | r | g | b
		);
}


void render_draw_sprite(struct Sprite sprite)
{
	//const int width = g2d_window->width * sprite.scale;
	//const int height = g2d_window->height * sprite.scale;

	//const struct Vec2 v = render_screen_to_px(sprite.pos);
	//int left = clamp(v.x - (width / 2), 0, g2d_window->width);
	//int right = clamp(v.x + (width / 2), 0, g2d_window->width);
	//int bottom = clamp(v.y - (height / 2), 0, g2d_window->height);
	//int top = clamp(v.y + (height / 2), 0, g2d_window->height);

	const float half_width = ((float)sprite.sprite_image->bi_width / (float)g2d_window->width);
	const float half_height = ((float)sprite.sprite_image->bi_height / (float)g2d_window->height);

	struct Vec2f vf_bl, vf_tr;
	vf_bl.x = sprite.pos.x + (sprite.pos_offset_x * half_width) - (half_width * sprite.scale);
	vf_bl.y = sprite.pos.y + (sprite.pos_offset_y * half_height) - (half_height * sprite.scale);
	vf_tr.x = sprite.pos.x + (sprite.pos_offset_x * half_width) + (half_width * sprite.scale);
	vf_tr.y = sprite.pos.y + (sprite.pos_offset_y * half_height) + (half_height * sprite.scale);

	//clampv(vf_bl, -1.0f, +1.0f);
	//clampv(vf_tr, -1.0f, +1.0f);

	const float step_x = 1.0f / (float)g2d_window->width;
	const float step_y = 1.0f / (float)g2d_window->height;
	for (float j = vf_bl.y; j < vf_tr.y; j += step_y)
	{
		for (float i = vf_bl.x; i < vf_tr.x; i += step_x)
		{
			struct Vec2f vf_translated;
			const float center_x = sprite.pos.x;//(sprite.pos.x + 1.0f) / 2.0f;
			const float center_y = sprite.pos.y;//(sprite.pos.y + 1.0f) / 2.0f;
			const float angle = sprite.angle + sprite.angle_offset;

			vf_translated.x = (i - center_x) * cos(angle) - (j - center_y) * sin(angle) + center_x;
			vf_translated.y = (i - center_x) * sin(angle) + (j - center_y) * cos(angle) + center_y;

			if (vf_translated.x < -1.0f || vf_translated.x >= 1.0f ||
				vf_translated.y < -1.0f || vf_translated.y >= 1.0f)
			{
				continue;
			}

			//vf = vector_multiply(vf, sprite.scale);

			render_draw_point_f(
				sprite_image_lookup(sprite.sprite_image,
				(i - vf_bl.x) / (vf_tr.x - vf_bl.x),
					(j - vf_bl.y) / (vf_tr.y - vf_bl.y)
				),
				vf_translated);
		}
	}




	//struct Vec2f vf;
	////const float a = fabs(sin(2.0f * sprite.angle));
	//const float step_x = (1.0f / ((float)sprite.info.bi_width ));
	//const float step_y = (1.0f / ((float)sprite.info.bi_height));
	//for (float j = 0.0f; j < 1.0f; j += step_y)
	//{
	//	for (float i = 0.0f; i < 1.0f; i += step_x)
	//	{
	//		const float center_x = sprite.pos.x;//(sprite.pos.x + 1.0f) / 2.0f;
	//		const float center_y = sprite.pos.y;//(sprite.pos.y + 1.0f) / 2.0f;

	//		const float scr_i = (i * 2.0f) - 1.0f;
	//		const float scr_j = (j * 2.0f) - 1.0f;
	//		vf.x = (scr_i - center_x) * cos(sprite.angle) - (scr_j - center_y) * sin(sprite.angle) + center_x;
	//		vf.y = (scr_i - center_x) * sin(sprite.angle) + (scr_j - center_y) * cos(sprite.angle) + center_y;

	//		vf = vector_multiply(vf, sprite.scale);

	//		render_draw_point_f(
	//			window_sprite_lookup(sprite, i, j), 
	//			vf);
	//	}
	//}




	//for (int j = bottom; j < top; j++)
	//{
	//	for (int i = left; i < right; i++)
	//	{
	//		const float x = (float)(i - left) / (float)width;
	//		const float y = (float)(j - bottom) / (float)height;
	//		const int xi = (i - v.x) * cos(sprite.angle) - (j - v.y) * sin(sprite.angle) + v.x;
	//		const int yi = (i - v.x) * sin(sprite.angle) + (j - v.y) * cos(sprite.angle) + v.y;

	//		render_draw_point(
	//			window_sprite_lookup(
	//				sprite,
	//				x,
	//				y
	//			),
	//			xi,
	//			yi);
	//	}
	//}
}
