#include "g2d.h"
#include <stdlib.h>

bool g2d_init()
{
	g2d_window = malloc(sizeof(struct G2D_Window));
	if (!g2d_window)
	{
		return false;
	}
	memset(g2d_window, 0, sizeof(struct G2D_Window));

	g2d_input = malloc(sizeof(struct G2D_Input));
	if (!g2d_input)
	{
		return false;
	}
	memset(g2d_input, 0, sizeof(struct G2D_Input));

	return true;
}

/* return event */
void g2d_poll_event()
{

}