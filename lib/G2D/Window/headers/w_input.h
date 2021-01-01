#ifndef G2D_INPUT_H
#define G2D_INPUT_H

#define MOUSE_WHEEL_DELTA 120

#define PROCESS_BUTTON(vk, btn)\
case vk:\
{\
	gp_g2d_input->buttons[btn].is_down = is_down;\
	gp_g2d_input->buttons[btn].changed = true;\
} break;


#define IS_DOWN(btn) (gp_g2d_input->buttons[btn].is_down)
#define PRESSED(btn) (gp_g2d_input->buttons[btn].is_down && gp_g2d_input->buttons[btn].changed)
#define RELEASED(btn) (!gp_g2d_input->buttons[btn].is_down && gp_g2d_input->buttons[btn].changed)


#define TYPING_ALLOWED_CHARS "0123456789abcdefghijklmnopqrstuvwxyz!£$*(){}[],.<>/?\;'#:@~`¬"


struct Button
{
	bool is_down;
	bool changed;
};


struct G2D_Input
{
	/* Mouse */
	bool mouse_raw_input;  /* Changes behaviour of mouse_pos */
	struct Vec2 mouse_pos;
	int mouse_scroll;
	bool mouse_in_window;

	/* Keyboard */
	struct Button buttons[BUTTON_COUNT];

	bool allow_typing;
	uint type_index;
	char type_buffer[128];
};

#endif