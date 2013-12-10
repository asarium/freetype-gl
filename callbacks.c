
#include <stdio.h>
#include <assert.h>

#include "callbacks.h"

void default_callback(message_type_t type, const char* message)
{
	switch(type)
	{
	case MESSAGE_ERROR:
		fprintf(stderr, "Error: %s\n", message);
		break;
	case MESSAGE_WARNING:
		fprintf(stdout, "Warning: %s\n", message);
		break;
	case MESSAGE_INFO:
		fprintf(stdout, "Information: %s\n", message);
		break;
	}
}

static message_callback_t message_callback = (message_callback_t) &default_callback;

void freetype_gl_set_message_callback(message_callback_t callback)
{
	assert(callback != NULL);

	message_callback = callback;
}

message_callback_t freetype_gl_get_message_callback()
{
	return message_callback;
}
