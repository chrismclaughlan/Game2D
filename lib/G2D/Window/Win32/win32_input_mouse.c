#include "../headers/w_win32.h"
#include "headers/win32_internal.h"

void window_input_mouse_event_move(int x, int y)
{
	gp_g2d_input->mouse_pos.x = x;
	gp_g2d_input->mouse_pos.y = y;
}

void window_input_mouse_event_scroll(int delta)
{
	gp_g2d_input->mouse_scroll += delta;
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
	gp_g2d_input->mouse_in_window = true;
}

void window_input_mouse_event_window_leave()
{
	gp_g2d_input->mouse_in_window = false;
}

bool window_input_mouse_is_within_rect(int x0, int y0, int x1, int y1)
{
	return (gp_g2d_input->mouse_pos.x > x0 && gp_g2d_input->mouse_pos.y > y0 && gp_g2d_input->mouse_pos.x <= x1 && gp_g2d_input->mouse_pos.y <= y1);
}

struct Vec2f window_input_mouse_get_screen_coords(void)
{
	return render_px_to_screen(gp_g2d_input->mouse_pos);
}