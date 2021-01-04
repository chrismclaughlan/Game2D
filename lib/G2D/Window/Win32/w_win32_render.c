#include "../w_win32.h"
#include <math.h>

void 
w_win32_render()
{
	StretchDIBits(
		gp_g2d_window->hdc, 0, 0, gp_g2d_window->width, gp_g2d_window->height,
		0, 0, gp_g2d_window->width, gp_g2d_window->height,
		gp_g2d_window->p_buffer, &gp_g2d_window->bitmap_info,
		DIB_RGB_COLORS, SRCCOPY
	);
}