#include "../headers/win32.h"

void window_input_keyboard_reset()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		g2d_input->buttons[i].is_down = false;
		g2d_input->buttons[i].changed = false;
	}
}

void window_input_keyboard_reset_changed()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		g2d_input->buttons[i].changed = false;
	}
}

void window_input_keyboard_event(uint vk_code, bool is_down)
{
	switch (vk_code)
	{
		PROCESS_BUTTON(VK_UP, BUTTON_UP);
		PROCESS_BUTTON(VK_DOWN, BUTTON_DOWN);
		PROCESS_BUTTON(VK_LEFT, BUTTON_LEFT);
		PROCESS_BUTTON(VK_RIGHT, BUTTON_RIGHT);


		PROCESS_BUTTON(0x57, BUTTON_W);
		PROCESS_BUTTON(0x41, BUTTON_A);
		PROCESS_BUTTON(0x53, BUTTON_S);
		PROCESS_BUTTON(0x44, BUTTON_D);

		PROCESS_BUTTON(0x30, BUTTON_0);
		PROCESS_BUTTON(0x31, BUTTON_1);
		PROCESS_BUTTON(0x32, BUTTON_2);
		PROCESS_BUTTON(0x33, BUTTON_3);
		PROCESS_BUTTON(0x34, BUTTON_4);
		PROCESS_BUTTON(0x35, BUTTON_5);
		PROCESS_BUTTON(0x36, BUTTON_6);
		PROCESS_BUTTON(0x37, BUTTON_7);
		PROCESS_BUTTON(0x38, BUTTON_8);
		PROCESS_BUTTON(0x39, BUTTON_9);

		//PROCESS_BUTTON(VK_SPACE, BUTTON_SPACE);
		PROCESS_BUTTON(VK_SPACE, BUTTON_LMOUSE);
	}
}

void window_input_keyboard_event_type(char vk_code)
{
	switch (vk_code)
	{
	case VK_BACK:
	{
		if (g2d_input->type_index > 0)
		{
			g2d_input->type_buffer[--g2d_input->type_index] = 0;
		}
	} break;
	case VK_RETURN:
	{
		/* Do something with string */
		memset(g2d_input->type_buffer, 0, sizeof(g2d_input->type_buffer));
		g2d_input->type_index = 0;
	} break;
	default:
	{
		VkKeyScanExA(vk_code, GetKeyboardLayout(0));
		g2d_input->type_buffer[g2d_input->type_index++] = vk_code;
	} break;
	}

	g2d_input->type_index = clamp(g2d_input->type_index, 0, sizeof(g2d_input->type_buffer));

	LOG_DEBUG("type_buffer [i=%d]: %s\n", g2d_input->type_index, g2d_input->type_buffer);
}