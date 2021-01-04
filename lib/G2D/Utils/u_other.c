#include "../utils.h"

bool 
u_char_in_string(char c, char* string)
{
	for (int i = 0; string[i] != 0; i++)
	{
		if (c == string[i]) return true;
	}

	return false;
}