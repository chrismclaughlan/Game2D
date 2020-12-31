#include "win32.h"
#include "../../Render/render.h"

void window_input_mouse_event_move(int x, int y)
{
	g2d_input->mouse_pos.x = x;
	g2d_input->mouse_pos.y = y;
}

void window_input_mouse_event_scroll(int delta)
{
	g2d_input->mouse_scroll += delta;
}

void window_input_mouse_event_click(uint vk_code, bool is_down)
{
	switch (vk_code)
	{
		PROCESS_BUTTON(VK_LBUTTON, BUTTON_LMOUSE)
			PROCESS_BUTTON(VK_RBUTTON, BUTTON_RMOUSE)
			PROCESS_BUTTON(VK_MBUTTON, BUTTON_MMOUSE)
			PROCESS_BUTTON(WM_LBUTTONUP, BUTTON_LMOUSE)
			PROCESS_BUTTON(WM_RBUTTONUP, BUTTON_RMOUSE)
			PROCESS_BUTTON(WM_MBUTTONUP, BUTTON_MMOUSE)
	}
}

void window_input_mouse_event_window_enter()
{
	g2d_input->mouse_in_window = true;
}

void window_input_mouse_event_window_leave()
{
	g2d_input->mouse_in_window = false;
}

bool window_input_mouse_is_within_rect(int x0, int y0, int x1, int y1)
{
	return (g2d_input->mouse_pos.x > x0 && g2d_input->mouse_pos.y > y0 && g2d_input->mouse_pos.x <= x1 && g2d_input->mouse_pos.y <= y1);
}

struct Vec2f window_input_mouse_get_screen_coords(void)
{
	return render_px_to_screen(g2d_input->mouse_pos);
}