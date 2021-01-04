#include "../g2d.h"
#include <stdlib.h>

bool g2d_init()
{
	LOG_DEBUG("initialising G2D\n");

	gp_g2d_window = malloc((sizeof *gp_g2d_window));
	if (!gp_g2d_window)
	{
		return false;
	}
	memset(gp_g2d_window, 0, sizeof(struct G2D_Window));

	gp_g2d_input = malloc((sizeof *gp_g2d_input));
	if (!gp_g2d_input)
	{
		return false;
	}
	memset(gp_g2d_input, 0, sizeof(struct G2D_Window_Input));

	(void)atexit(g2d_cleanup);

	return true;
}

void g2d_cleanup()
{
	/* TODO */
	(void)free(gp_g2d_window);
	(void)free(gp_g2d_input);
}

/* return event */
void g2d_poll_event()
{
	/* TODO */
}