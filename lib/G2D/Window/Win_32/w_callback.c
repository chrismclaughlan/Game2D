#include "../headers/win32.h"
#include <windowsx.h>  /* get x/y param*/
#include <WinUser.h>  /* get wheel delta param */

/**
 * https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
 * 
 * https://stackoverflow.com/questions/7247601/how-to-exit-win32-application-via-api
 */
LRESULT
window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;

	switch (msg)
	{
	/* Window */
	case WM_KILLFOCUS:
	{
		LOG_DEBUG("LOST FOCUS\n");

		window_input_keyboard_reset();
	} break;
	case WM_CLOSE:
	{
		/* Cascades to WM_DESTROY ... */

		/* Perform cleanup */

		/* Window console */
		(void)FreeConsole();
	} break;
	case WM_DESTROY:
	{
		/* Cascades to WM_QUIT ... */
		PostQuitMessage(0);
	} break;
	case WM_SIZE:
	{
		const int new_width = GET_X_LPARAM(lparam);
		const int new_height = GET_Y_LPARAM(lparam);

		LOG_DEBUG("WM_SIZE width %d height %d\n", new_width, new_height);

		g2d_window->width = new_width;
		g2d_window->height = new_height;

		if (g2d_window->pbuffer)
		{
			VirtualFree(g2d_window->pbuffer, 0, MEM_RELEASE);
		}

		int buffer_size = sizeof(uint32) * g2d_window->width * g2d_window->height;
		g2d_window->pbuffer = VirtualAlloc(NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		g2d_window->bitmap_info.bmiHeader.biSize = sizeof(g2d_window->bitmap_info.bmiHeader);
		g2d_window->bitmap_info.bmiHeader.biWidth = g2d_window->width;
		g2d_window->bitmap_info.bmiHeader.biHeight = g2d_window->height;
		g2d_window->bitmap_info.bmiHeader.biPlanes = 1;
		g2d_window->bitmap_info.bmiHeader.biBitCount = 32;
		g2d_window->bitmap_info.bmiHeader.biCompression = BI_RGB;

		LOG_DEBUG("width %d height %d\n", g2d_window->width, g2d_window->height);
	} break;

	/* Keyboard */
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		uint vk_code = wparam;
		bool is_down = ((lparam & (1 << 31)) == 0);
		//bool was_down = ((lparam & (1 << 30)) != 0);

		window_input_keyboard_event(vk_code, is_down);
	} break;

	/* Keyboard typing */
	case WM_CHAR:
	{
		/* If capture typing... */
		if (g2d_input->allow_typing)
		{
			window_input_keyboard_event_type(wparam);
		}
	} break;

	/* Mouse */
	case WM_INPUT:
	{
		if (g2d_input->mouse_raw_input)
		{
			UINT dwSize = sizeof(RAWINPUT);
			static BYTE lpb[sizeof(RAWINPUT)];

			GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				g2d_input->mouse_pos.x = raw->data.mouse.lLastX;
				g2d_input->mouse_pos.y = raw->data.mouse.lLastY;
			}
		}
	} break;

	case WM_MOUSEMOVE:
	{
		if (!g2d_input->mouse_raw_input)
		{
			const int x = GET_X_LPARAM(lparam);
			const int y = g2d_window->height - GET_Y_LPARAM(lparam);  /* flip y-axis */

			if (x < 0 || y < 0 || x >= g2d_window->width || y >= g2d_window->height)
			{
				/* Outside window */
				if (wparam & (MK_LBUTTON | MK_RBUTTON))
				{
					/* Dragging */
					window_input_mouse_event_move(x, y);
				}
				else
				{
					ReleaseCapture();
					window_input_mouse_event_window_leave();
				}
			}
			else  
			{
				/* Inside window */
				window_input_mouse_event_move(x, y);

				if (!g2d_input->mouse_in_window)  /* If mouse wasn't in window before: */
				{
					SetCapture(hwnd);
					window_input_mouse_event_window_enter();
				}
			}
		}
	} break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	{
		const uint vk_code = wparam;
		window_input_mouse_event_click(vk_code, true);
	} break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	{
		const uint vk_code = msg;  /* note: switch(msg) ... */
		window_input_mouse_event_click(vk_code, false);
	} break;

	case WM_MOUSEWHEEL:
	{
		window_input_mouse_event_scroll(GET_WHEEL_DELTA_WPARAM(wparam));
		LOG_DEBUG("scroll: %d", g2d_input->mouse_scroll)
	} break;
	}

	return DefWindowProcA(hwnd, msg, wparam, lparam);;
}
