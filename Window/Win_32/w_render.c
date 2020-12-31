#include "win32.h"
#include <math.h>
//#include "../utils.h"

void window_render()
{
	StretchDIBits(
		g2d_window->hdc, 0, 0, g2d_window->width, g2d_window->height,
		0, 0, g2d_window->width, g2d_window->height,
		g2d_window->pbuffer, &g2d_window->bitmap_info,
		DIB_RGB_COLORS, SRCCOPY
	);
}