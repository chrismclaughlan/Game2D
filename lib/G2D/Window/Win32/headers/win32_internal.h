#ifndef G2D_WIN32_INTERNAL_H
#define G2D_WIN32_INTERNAL_H


#include "hwindows.h"


LRESULT window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


/* - - - - - - - - Input - - - - - - - - */

/* Keyboard */
void window_input_keyboard_reset(void);
void window_input_keyboard_reset_changed(void);
void window_input_keyboard_event(uint vk_code, bool is_down);
void window_input_keyboard_event_type(char vk_code);

/* Mouse */
void window_input_mouse_event_move(int x, int y);
void window_input_mouse_event_scroll(int delta);
void window_input_mouse_event_click(uint vk_code, bool is_down);
void window_input_mouse_event_window_enter();
void window_input_mouse_event_window_leave();


#endif