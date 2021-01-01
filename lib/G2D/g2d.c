#include "headers/g2d.h"
#include <stdlib.h>

bool g2d_init()
{
	gp_g2d_window = malloc(sizeof(struct G2D_Window));
	if (!gp_g2d_window)
	{
		return false;
	}
	memset(gp_g2d_window, 0, sizeof(struct G2D_Window));

	gp_g2d_input = malloc(sizeof(struct G2D_Input));
	if (!gp_g2d_input)
	{
		return false;
	}
	memset(gp_g2d_input, 0, sizeof(struct G2D_Input));

	return true;
}

/* return event */
void g2d_poll_event()
{
	/* TODO */
}