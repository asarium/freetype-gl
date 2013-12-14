
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

static message_callback_t message_callback = &default_callback;

void freetype_gl_set_message_callback(message_callback_t callback)
{
	assert(callback != NULL);

	message_callback = callback;
}

message_callback_t freetype_gl_get_message_callback()
{
	return message_callback;
}

int default_filesystem_callback(const char* filename, void* buffer, size_t* size)
{
	FILE * file;
	size_t file_size;

	file = fopen(filename, "rb");
	if (!file)
	{
		char message[128];
		sprintf(message, "Unable to open file \"%s\".", filename);

		freetype_gl_get_message_callback()(MESSAGE_WARNING, message);

		return 0;
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);

	if (buffer != NULL)
	{
		fseek(file, 0, SEEK_SET);
		fread(buffer, sizeof(char), file_size, file);
	}

	if (size != NULL)
	{
		*size = file_size;
	}

	fclose(file);

	return 1;
}

static filesystem_callback_t filesystem_callback = &default_filesystem_callback;

void freetype_gl_set_filesystem_callback(filesystem_callback_t callback)
{
	assert(callback != NULL);

	filesystem_callback = callback;
}

filesystem_callback_t freetype_gl_get_filesystem_callback()
{
	return filesystem_callback;
}
