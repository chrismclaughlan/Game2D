#include "../w_win32.h"
#include "headers/w_win32_internal.h"

#include <stdio.h>
#include <hidusage.h>
//#include <direct.h>
#include <direct.h>
#include <tchar.h>
#include <stdlib.h>

/**
 * Changes working directory to that containing the executable.
 */
static bool 
window_working_dir_change()
{
	TCHAR path_buffer[MAX_PATH] = { 0 };

	//if (GetCurrentDirectory(MAX_PATH, path_buffer))
	//{
	//	LOG_DEBUG("GetCurrentDirectory() failed\n");
	//	return false;
	//}

	/* Get path to .exe directory*/
	if (GetModuleFileName(NULL, path_buffer, MAX_PATH) == 0)
	{
		LOG_DEBUG("GetModuleFileName() failed\n");
		return false;
	}

	/* Cut off executable from path */
	for (int i = (int)_tcslen(path_buffer); i > 0; i--)
	{
		if (path_buffer[i] == 92)  /* 92 = '\' */
		{
			path_buffer[i + 1] = 0;
			break;
		}
	}

	/* Change dir */
	if (_tchdir(path_buffer) != 0)
	{
		LOG_DEBUG("w_chdir() failed\n");
		return false;
	}

	return true;
}

bool 
w_win32_create(HINSTANCE hInstance, uint window_width, uint window_height, char* window_name)
{
	if (!window_working_dir_change())
	{
		LOG_DEBUG("Error: Failed to change working directory, \
					some resources may not load correctly!\n");
	}

	/* Display console to log stderr */
	(void) AllocConsole();
	//if (!AttachConsole(GetCurrentProcessId()))
	//{
	//	/* Error */
	//}
	errno_t err = freopen_s(&gp_g2d_window->f_window_console, "CON", "w", stderr);
	if (err != 0)
	{
		/* TODO: if not fatal just ignore and continue as if not debug mode */
		return false;
	}

	gp_g2d_window->hinstance = hInstance;

	/* Register class */
	WNDCLASSEX window_class = { 0 };
	window_class.cbSize = sizeof(window_class);
	window_class.style = CS_OWNDC;
	window_class.lpfnWndProc = w_win32_callback;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = hInstance;
	window_class.hIcon = NULL;
	window_class.hCursor = NULL;
	window_class.hbrBackground = NULL;
	window_class.lpszMenuName = NULL;
	window_class.lpszClassName = G2D_WINDOW_CLASS_NAME;
	window_class.hIconSm = NULL;

	if (!RegisterClassEx(&window_class))
	{
		MessageBox(NULL, "G2D Error: Failed to register window class (WNDCLASSEX).", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	/* Window sizing */
	RECT rect;
	rect.left = 100;
	rect.right = window_width + rect.left;
	rect.top = 100;
	rect.bottom = window_height + rect.top;

	// WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
	// WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME
	(void)AdjustWindowRect(&rect, WS_VISIBLE | WS_OVERLAPPEDWINDOW, FALSE);

	gp_g2d_window->hwnd = CreateWindowEx(
		0,                                  // Optional window styles.
		window_class.lpszClassName,         // Window class
		window_name,                      // Window text
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,   // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,

		NULL,			// Parent window    
		NULL,			// Menu
		hInstance,		// Instance handle
		NULL			// Additional application data
	);
	if (gp_g2d_window->hwnd == NULL)
	{
		MessageBox(NULL, "G2D Error: Failed to create window (HWND).", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	/* Raw input */
	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = gp_g2d_window->hwnd;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	if (!(gp_g2d_window->hdc = GetDC(gp_g2d_window->hwnd)))
	{
		MessageBox(NULL, "G2D Error: Failed to get handle for device context (HDC).", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	//LOG_DEBUG("WINDOW CREATE width: %d height %d\n", render_buffer.width, render_buffer.height)

	(void)atexit(w_win32_destroy);  /* TODO */


	if (!w_win32_sound_manager_init())
	{
		LOG_ERROR("w_win32_sound_manager()\n");
	}


	(void)ShowWindow(gp_g2d_window->hwnd, SW_SHOWDEFAULT);
	(void)SetForegroundWindow(gp_g2d_window->hwnd);

	w_win32_focus_set();

	return true;
}